/**************************************************
*                                                 *
*   MultiThreaded - Dictionary - Shuffle & Sort   *
*   written by: Hadar Klein                       *
*   reviewed by: Yoni Wainsztok                   *
*                                                 *
**************************************************/

#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <string.h>     /* strcmp */
#include <sys/mman.h>   /* mmap, munmap */
#include <sys/stat.h>   /* stat structure */
#include <fcntl.h>      /* open */
#include <unistd.h>     /* close */
#include <stdlib.h>     /* abort */

#include <pthread.h>    /* threads */

#include "utils.h"      /* utils */

#define g_UPLOAD_THREADS (3)
#define g_WORDS_IN_DICT (99171)
#define g_TOTAL_WORDS (g_UPLOAD_THREADS * g_WORDS_IN_DICT)
#define g_SORTING_THREADS (4)
#define g_MERGING_THREADS (2)
#define DIR ("/home/student/words")

struct thread_arg
{
    size_t idx;
    size_t size;
    size_t lower_bound;
    size_t upper_bound;
    size_t num_of_elements;
    size_t start_pos;
};

struct thread_arg_merge
{
    size_t idx;
    struct thread_arg arg1;
    struct thread_arg arg2;
};


typedef struct words
{
    char *word;
}word_t;

static const int g_NUM_OF_WORDS = g_WORDS_IN_DICT;
static word_t g_WORD_ARR[g_WORDS_IN_DICT * g_UPLOAD_THREADS] = {0};
static char *g_DICT_ARR[g_UPLOAD_THREADS] = {0};

static void *ThreadUploadDict(void *arg);
static char *OpenDictionary(size_t *size);
static void UnMap(void *region, size_t size);
static size_t getFilesize(const char* filename);
static void BuildDictShuffleAndSort();
static void UploaderThreads(struct thread_arg *thread_arg_array);
static void CheckPthreadCreate(int retval);
static void UploadToArray(char *region, int lower_bound, int upper_bound);
static void PrintDictionaries();
static void ShuffleDictionary();
static void SortDictionary();
static int StrCmpWrapper(const void *a, const void *b);



int main()
{
    srand(time(NULL));

    BuildDictShuffleAndSort();

    return 0;
}


static void BuildDictShuffleAndSort()
{
    int i = 0;
    struct thread_arg uploader_thread_arg_array[g_UPLOAD_THREADS] = {0};
    
    UploaderThreads(uploader_thread_arg_array);

    ShuffleDictionary();
     
    SortDictionary();

    for (i = 0; i < g_UPLOAD_THREADS; ++i)
    {
       UnMap(g_DICT_ARR[i], uploader_thread_arg_array[i].size);
    }
}


static int StrCmpWrapper(const void *a, const void *b)
{
    word_t *first = (word_t *)a;
    word_t *second = (word_t *)b;

    assert(NULL != a);
    assert(NULL != b);

    return strcmp(first->word, second->word);
}


static void *ThreadQuickSort(void *arg)
{
    struct thread_arg *temp = (struct thread_arg *)arg;

    assert(NULL != arg);

    qsort(&g_WORD_ARR[temp->start_pos], temp->num_of_elements, 
          sizeof(char *), StrCmpWrapper);

    return NULL;
}

static void InitThreadArgArray(struct thread_arg *thread_arg_array,
                               int num_of_threads, int total_threads,
                               int num_of_elements)
{
    int i = 0;

    for (i = 0; i < num_of_threads; ++i)
    {
        thread_arg_array[i].idx = i;
        thread_arg_array[i].num_of_elements = num_of_elements;
        thread_arg_array[i].start_pos = i * num_of_elements;
    }
    thread_arg_array[i - 1].num_of_elements += 
                                 g_TOTAL_WORDS % total_threads;
}

static void SortDictInternalSort()
{
    int i = 0;
    int retval = 0;
    int num_of_elements = g_TOTAL_WORDS / g_SORTING_THREADS;
    struct thread_arg sorting_thread_arg_array[g_SORTING_THREADS] = {0};
    pthread_t sorting_thread_array[g_SORTING_THREADS];

    InitThreadArgArray(sorting_thread_arg_array, g_SORTING_THREADS,
                       g_SORTING_THREADS, num_of_elements);

    for (i = 0; i < g_SORTING_THREADS; ++i)
    {
        retval = pthread_create(&sorting_thread_array[i], NULL,
                                ThreadQuickSort, &sorting_thread_arg_array[i]);
        CheckPthreadCreate(retval);
    }

    for (i = 0; i < g_SORTING_THREADS; ++i)
    {
        pthread_join(sorting_thread_array[i], NULL);
    }
}


static void *MergeIMP(void *arg)
{
    struct thread_arg_merge *temp_arg = (struct thread_arg_merge *)arg;

    word_t temp_arr[g_TOTAL_WORDS] = {0};
    size_t  idx = 0;
    size_t total_size = temp_arg->arg1.num_of_elements + 
                      temp_arg->arg2.num_of_elements;
    size_t i = temp_arg->arg1.start_pos;
    size_t j = temp_arg->arg2.start_pos;
    size_t k = temp_arg->arg1.start_pos;
    size_t i_length = temp_arg->arg1.start_pos + temp_arg->arg1.num_of_elements;
    size_t j_length = temp_arg->arg2.start_pos + temp_arg->arg2.num_of_elements;

    assert(NULL != arg);

    while (i < i_length && j < j_length)
    {
        if (0 >= strcmp(g_WORD_ARR[i].word, g_WORD_ARR[j].word))
        {
            temp_arr[idx] = g_WORD_ARR[i++];
        }
        else
        {
            temp_arr[idx] = g_WORD_ARR[j++];
        }
        ++idx;
    }

    while (i < temp_arg->arg1.start_pos + temp_arg->arg1.num_of_elements)
    {
        temp_arr[idx++] = g_WORD_ARR[i++];
    }
    while (j < j_length)
    {
        temp_arr[idx++] = g_WORD_ARR[j++];
    }

    for (i = 0; i < total_size; ++i, ++k)
    {
        g_WORD_ARR[k] = temp_arr[i];
    }

    return NULL;
}


static void MergeArraysFourToTwo()
{
    int i = 0;
    int retval = 0;
    int range = g_TOTAL_WORDS / g_SORTING_THREADS;
    struct thread_arg merging_thread_arg_array[g_SORTING_THREADS] = {0};
    struct thread_arg_merge merge_args_array[g_MERGING_THREADS] = {0};
    pthread_t merging_thread_array[g_MERGING_THREADS];


    InitThreadArgArray(merging_thread_arg_array, g_SORTING_THREADS,
                       g_MERGING_THREADS, range);

    merge_args_array[0].arg1 = merging_thread_arg_array[0];
    merge_args_array[0].arg2 = merging_thread_arg_array[1];
    merge_args_array[1].arg1 = merging_thread_arg_array[2];
    merge_args_array[1].arg2 = merging_thread_arg_array[3];

    for (i = 0; i < g_MERGING_THREADS; ++i)
    {
        retval = pthread_create(&merging_thread_array[i], NULL,
                                MergeIMP, &merge_args_array[i]);
        CheckPthreadCreate(retval);
    }

    for (i = 0; i < g_MERGING_THREADS; ++i)
    {
        pthread_join(merging_thread_array[i], NULL);
    }
}


static void MergeArraysTwoToOne()
{
    struct thread_arg_merge merge_arg = {0};
    int partitions = 2;
    int range = g_TOTAL_WORDS / partitions;
    
    merge_arg.arg1.num_of_elements = range;
    merge_arg.arg1.start_pos = 0 * range;
    merge_arg.arg2.num_of_elements = range + (g_TOTAL_WORDS % partitions);
    merge_arg.arg2.start_pos = 1 * range;

    MergeIMP(&merge_arg);
}


static void SortDictionary()
{
    SortDictInternalSort();
    MergeArraysFourToTwo();
    MergeArraysTwoToOne();
}


static void PrintDictionaries()
{
    int i = 0;

    for (i = 0; i < g_TOTAL_WORDS; ++i)
    {
        printf ("%d %s\n",i, g_WORD_ARR[i].word);
    }
}


static void ShuffleDictionary()
{
    int i = 0;
    int arr_size = g_UPLOAD_THREADS * g_NUM_OF_WORDS;
    word_t temp = {0};
    int rand_idx = 0;

    for (i = 0; i < arr_size / 2; ++i)
    {
        rand_idx = rand() % arr_size;
        temp = g_WORD_ARR[i];
        g_WORD_ARR[i] = g_WORD_ARR[rand_idx];
        g_WORD_ARR[rand_idx] = temp;
    }
}


static void UploaderThreads(struct thread_arg *thread_arg_array)
{
    int i = 0;
    int retval = 0;
    pthread_t uploader_thread_array[g_UPLOAD_THREADS];

    assert(NULL != thread_arg_array);

    for (i = 0; i < g_UPLOAD_THREADS; ++i)
    {
        thread_arg_array[i].idx = i;
        thread_arg_array[i].lower_bound = (i * g_NUM_OF_WORDS);
        thread_arg_array[i].upper_bound = ((i + 1) * g_NUM_OF_WORDS);
    }
    
    for (i = 0; i < g_UPLOAD_THREADS; ++i)
    {
        retval = pthread_create(&uploader_thread_array[i], NULL,
                                ThreadUploadDict , &thread_arg_array[i]);
        CheckPthreadCreate(retval);
    }

    for (i = 0; i < g_UPLOAD_THREADS; ++i)
    {
        pthread_join(uploader_thread_array[i], NULL);
    }
}


static void CheckPthreadCreate(int retval)
{
    if (SUCCESS != retval)
    {
        fprintf(stderr, "There was a problem during thread creation\n");
        abort();
    }
}


static void *ThreadUploadDict(void *arg)
{
    struct thread_arg *temp = (struct thread_arg*)arg;

    assert(NULL != arg);

    g_DICT_ARR[temp->idx] = OpenDictionary(&temp->size);

    UploadToArray(g_DICT_ARR[temp->idx], temp->lower_bound, temp->upper_bound);

    return NULL;
}


static void UploadToArray(char *region, int lower_bound, int upper_bound)
{
    int start = lower_bound;
    int end = upper_bound;

    assert(NULL != region);
    assert(lower_bound <= upper_bound);

    while ((start < end) && ('\0' != *region))
    {
        g_WORD_ARR[start++].word = region;

        while ('\n' != *region)
        {
            ++region;
        }
        *region = '\0';
        ++region;
    }
}


static void UnMap(void *region, size_t size)
{
    assert(NULL != region);

    if (-1 == munmap(region, size))
    {
        perror("Error during virtual memory unmapping\n");
        exit(1);
    } 
}


static size_t getFilesize(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}


static char *OpenDictionary(size_t *size)
{
    char *region = NULL;
    char *region_start = NULL;
    int fd = 0;

    assert(NULL != size);

    fd = open(DIR, 0);
    if (-1 == fd)
    {
        perror("Error during attempt to open file for mapping to\
                 virtual memory\n");
        exit(1);
    }

    *size = getFilesize(DIR);
    region = mmap(NULL, *size, PROT_WRITE, MAP_PRIVATE, fd, 0);
    region_start = region;
    if (NULL == region)
    {
        perror("Error during memory mapping\n");
        exit(1);
    }
    
    close(fd);

    return region_start;
}
