/***********************************
*                                  *
*   DS -                           *
*   written by: Hadar Klein        *
*   reviewed by:                   *
*                                  *
***********************************/

#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

/* #include "multithreaddicthistogram.h" */
#include "utils.h"

#define SUCCESSFUL 0
#define g_NUM_OF_CHARS 256

static char *OpenDictionary(size_t *size);
static void UnMap(void *region, size_t size);
static size_t getFilesize(const char* filename);
static void *ThreadCountLetters(void *arg);
static void BuildHistogram();
static void BuildHistogramIMP(int *histogram);
static void BuildHistogramArgv();
static void BuildHistogramARGVIMP(int *histogram, int num_of_threads);
static void *ThreadCountLettersArgv(void *arg);

static void PrintHistogramIMP(int *histogram);



static volatile size_t g_LETTER_ARRAY[g_NUM_OF_THREADS][g_NUM_OF_CHARS] = {0};
static volatile size_t **g_LETTER_ARRAY_ARGV = NULL;


struct thread_arg
{
    size_t idx;
    char *lower_bound;
    char *upper_bound;
};


int main(int argc, char **argv)
{
    if (1 == argc)
    {
        printf("define\n");
        BuildHistogram();
    }
    else
    {
        printf("shell\n");
        BuildHistogramArgv(argv);
    }
    
    return 0;
}





static void BuildHistogramArgv(char **args)
{
    int i = 0;
    int retval = 0ul;
    char *dictionary = NULL;
    size_t size = 0ul;
    size_t range = 0ul;
    int histogram[g_NUM_OF_CHARS] = {0};
    int num_of_threads = atoi(args[1]);
    
    struct thread_arg *thread_arg_array = malloc(num_of_threads * 
                                                 sizeof(struct thread_arg));
    pthread_t *thread_array = malloc(num_of_threads * sizeof(pthread_t));

    g_LETTER_ARRAY_ARGV = calloc(num_of_threads, sizeof(size_t **));

    for (i = 0ul; i < num_of_threads; ++i)
    {
        g_LETTER_ARRAY_ARGV[i] = calloc(g_NUM_OF_CHARS, sizeof(size_t *));
    }

    dictionary = OpenDictionary(&size);

    range = size / num_of_threads;

    for (i = 0ul; i < num_of_threads; ++i)
    {
        thread_arg_array[i].idx = i;
        thread_arg_array[i].lower_bound = dictionary + (range * i);
        thread_arg_array[i].upper_bound = dictionary + (range * (i + 1)) - 1;

    }
    thread_arg_array[i-1].upper_bound = dictionary + size;


    for (i = 0ul; i < num_of_threads; ++i)
    {
        retval = pthread_create(&(thread_array[i]), NULL,
                                ThreadCountLettersArgv, 
                                &thread_arg_array[i]);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr, "Thread number %d return an error %d\n", i,
                    retval);
        }
    }

    for (i = 0; i < num_of_threads; ++i)
    {
        retval = pthread_join(thread_array[i], NULL);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr,"Thread number %d returned an error %d\n", i,
                    retval);
            exit(1);
        }
    }

    BuildHistogramARGVIMP(histogram, num_of_threads);
    PrintHistogramIMP(histogram);

    /* at the end release the dictionary */
    UnMap(dictionary, size);
    free(thread_array);
    free(thread_arg_array);
    for (i = 0ul; i < num_of_threads; ++i)
    {
        free(g_LETTER_ARRAY_ARGV[i]);
    }
    free(g_LETTER_ARRAY_ARGV);
}


static void *ThreadCountLettersArgv(void *arg)
{
    struct thread_arg temp_arg = *(struct thread_arg*)arg;
    unsigned char token = '\0';
    while (temp_arg.lower_bound != temp_arg.upper_bound)
    {
        token = *temp_arg.lower_bound;
        /* ++*(g_LETTER_ARRAY_ARGV + (temp_arg.idx * (int)token)); */
        
        ++g_LETTER_ARRAY_ARGV[temp_arg.idx][(int)token];
        temp_arg.lower_bound += 1;
    }
    
    return NULL;
}


static void BuildHistogramARGVIMP(int *histogram, int num_of_threads)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < num_of_threads; ++i)
    {
        for (j = 0; j < g_NUM_OF_CHARS; ++j)
        {
            histogram[j] += g_LETTER_ARRAY_ARGV[i][j];
        }
    }
}



static void BuildHistogram()
{
    size_t i = 0ul;
    size_t retval = 0ul;
    char *dictionary = NULL;
    size_t size = 0ul;
    size_t range = 0ul;
    struct thread_arg thread_arg_array[g_NUM_OF_THREADS] = {0};
    pthread_t thread_array[g_NUM_OF_THREADS];
    int histogram[g_NUM_OF_CHARS] = {0};

    dictionary = OpenDictionary(&size);

    range = size / g_NUM_OF_THREADS;

    for (i = 0ul; i < g_NUM_OF_THREADS; ++i)
    {
        thread_arg_array[i].idx = i;
        thread_arg_array[i].lower_bound = dictionary + (range * i);
        thread_arg_array[i].upper_bound = dictionary + (range * (i + 1)) - 1;

    }
    thread_arg_array[i-1].upper_bound = dictionary + size;


    for (i = 0ul; i < g_NUM_OF_THREADS; ++i)
    {
        retval = pthread_create(&(thread_array[i]), NULL,
                                ThreadCountLetters, 
                                &thread_arg_array[i]);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr, "Thread number %lu return an error %lu\n", i,
                    retval);
        }
    }

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        retval = pthread_join(thread_array[i], NULL);
        if (SUCCESSFUL != retval)
        {
            fprintf(stderr,"Thread number %lu returned an error %lu\n", i,
                    retval);
            exit(1);
        }
    }

    BuildHistogramIMP(histogram);
    PrintHistogramIMP(histogram);

    /* at the end release the dictionary */
    UnMap(dictionary, size);
}


static void PrintHistogramIMP(int *histogram)
{
    int i = 0;

    for (i = 0; i < g_NUM_OF_CHARS; ++i)
    {
        if (0 != histogram[i])
        {
            if (i == 10)
            {
                printf("The frequency of \\n was %d\n", histogram[i]);    
            }
            else
            {
                printf("The frequency of %c was %d\n", i, histogram[i]);
            }
        }
    }
}




static void BuildHistogramIMP(int *histogram)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < g_NUM_OF_THREADS; ++i)
    {
        for (j = 0; j < g_NUM_OF_CHARS; ++j)
        {
            histogram[j] +=  g_LETTER_ARRAY[i][j];
        }
    }
}

static void *ThreadCountLetters(void *arg)
{
    struct thread_arg temp_arg = *(struct thread_arg*)arg;
    unsigned char token = '\0';
    while (temp_arg.lower_bound != temp_arg.upper_bound)
    {
        token = *temp_arg.lower_bound;
        ++g_LETTER_ARRAY[temp_arg.idx][(int)token];
        temp_arg.lower_bound += 1;
    }
    
    return NULL;
}

static char *OpenDictionary(size_t *size)
{
    char *region = NULL;
    char *region_start = NULL;

    int fd =  open("/home/student/words", 0);
    if (-1 == fd)
    {
        perror("Error during attempt to open file for mapping to\
                 virtual memory\n");
        exit(1);
    }

    *size = getFilesize("/home/student/words");
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

static void UnMap(void *region, size_t size)
{
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
