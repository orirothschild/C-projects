#include <stdio.h> /* printf */
#include <string.h> /* string cmp */
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "hash.h"
#include "hash_test_funcs.h"
#include "utils.h"

size_t HashFunc(void *key);
int HashCmpFunc(const void *user_data, const void *table_data,
                                void *param);
int HashActionFuncSucceed(void *table_data, void *param);
int HashActionFuncFail(void *table_data, void *param);
void APP(void);

char *InsertDictionaryIntoHashTable(hash_t *hash_table, size_t *size);
void UnMap(void *region, size_t size);

int HashActionFunc(void *table_data, void *param);

size_t getFilesize(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}


int main()
{
    RUN_TEST(TEST_Hashtable_Create());
    RUN_TEST(TEST_HashTable_Size());
    RUN_TEST(TEST_HashTable_Variance());
    RUN_TEST(TEST_HashTable_IsEmpty_True());
    RUN_TEST(TEST_HashTable_IsEmpty_False());
    RUN_TEST(TEST_HashTable_Find_True());
    RUN_TEST(TEST_HashTable_Find_False());
    RUN_TEST(TEST_HashTable_Remove());
    RUN_TEST(TEST_HashTable_Remove_Remove());
    RUN_TEST(TEST_HashTable_ForEach_True());
    RUN_TEST(TEST_HashTable_ForEach_False());

    APP();


    return (0);
}



int TEST_Hashtable_Create()
{
    hash_t *hash_table = NULL;

    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;

    hash_table = HashCreate(size, hash_func, cmp_func);

    if (NULL != hash_table)
    {
        HashDestroy(hash_table);
        return PASS;
    }

    HashDestroy(hash_table);
    return FAIL;
}


int TEST_HashTable_Size()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    char *region = NULL;
    size_t dict_size = 0;


    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    if (99171 == HashSize(hash_table))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_Variance()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    HashVariance((const hash_t *)hash_table);

    if (99171 == HashSize(hash_table))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_IsEmpty_True()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;

    hash_table = HashCreate(size, hash_func, cmp_func);

    if (True == HashIsEmpty(hash_table))
    {
        HashDestroy(hash_table);
        return PASS;
    }

    HashDestroy(hash_table);
    return FAIL;
}


int TEST_HashTable_IsEmpty_False()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    if (False == HashIsEmpty(hash_table))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_Find_True()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    if (IDENTICAL == strcmp(HashFind(hash_table, "Aberdeen"), "Aberdeen"))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_Find_False()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    if (NULL == HashFind(hash_table, "blerg"))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_Remove()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    HashRemove(hash_table, "Aberdeen");

    if (NULL == HashFind(hash_table, "Aberdeen"))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_Remove_Remove()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    HashRemove(hash_table, "Aberdeen");
    HashRemove(hash_table, "Aberdeen");

    if (NULL == HashFind(hash_table, "Aberdeen"))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_ForEach_True()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    void *param = &size;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    if (SUCCESS == HashForEach((const hash_t *)hash_table, HashActionFuncSucceed, 
                                param))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


int TEST_HashTable_ForEach_False()
{
    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    void *param = &size;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);

    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);

    if (FAILURE == HashForEach((const hash_t *)hash_table, HashActionFuncFail, 
                                param))
    {
        HashDestroy(hash_table);
        UnMap(region, dict_size);
        return PASS;
    }

    HashDestroy(hash_table);
    UnMap(region, dict_size);
    return FAIL;
}


void APP(void)
{
    char str[100] = {0};

    hash_t *hash_table = NULL;
    size_t size = 599;
    hash_func_t hash_func = HashFunc;
    hash_cmp_func_t cmp_func = HashCmpFunc;
    size_t dict_size = 0;
    char *region = NULL;

    hash_table = HashCreate(size, hash_func, cmp_func);
    region = InsertDictionaryIntoHashTable(hash_table, &dict_size);


    printf("please write a word to check in the dictionary\n");
    printf("enter '/' to quit\n\n");
    scanf("%s", str);

    while ('/' != str[0])
    {
        if (NULL == HashFind(hash_table, str))
        {
            printf("%s does not exist in the dictionary\n\n", str);
        }   
        else
        {
            printf("%s exists in the dictionary\n\n", str);
        }
        
        printf("please write a word to check in the dictionary\n");
        scanf("%s", str);    
    }
    
    HashDestroy(hash_table);
    UnMap(region, dict_size);
}


/******************************************************************************/
size_t HashFunc(void *key)
{
    char *str = (char *)key;
    int sum = 0;
    int i = 0;

    while ('\0' != *str)
    {
        sum += *str++ * ++i;
    }
    
    return sum;
}


int HashActionFuncSucceed(void *table_data, void *param)
{
    (void)table_data;
    (void)param;
    
    return SUCCESS;
}


int HashActionFuncFail(void *table_data, void *param)
{
    (void)table_data;
    (void)param;
    
    return FAILURE;
}


int HashCmpFunc(const void *user_data, const void *table_data,
                                void *param)
{
    (void)param;
    return strcmp(user_data, table_data);
}


char *InsertDictionaryIntoHashTable(hash_t *hash_table, size_t *size)
{
    char *region = NULL;
    char *str = NULL;
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
    
    
    while ('\0' != *region)
    {
        str = region;
        while ('\n' != *region)
        {
            /* printf("%c", *region); */
            ++region;
        }
        *region = '\0';
        if (FAILURE == HashInsert(hash_table, str))
        {
            return NULL;
        }
        ++region;
    }

    return region_start;
}

void UnMap(void *region, size_t size)
{
    if (-1 == munmap(region, size))
    {
        perror("Error during virtual memory unmapping\n");
        exit(1);
    } 
}