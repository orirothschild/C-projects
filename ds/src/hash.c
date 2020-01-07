/***********************************
*                                  *
*   DS - Hash Table                *
*   written by: Hadar Klein        *
*   date: 15.1.19                  *
*   reviewed by: Bar Shoshany      *
*                                  *
***********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "hash.h"   /*  API   */
#include "utils.h"  /* utills */


#define POINTER_SIZE 8

struct hash_table
{
    size_t table_size;
    dlist_t **table;
    hash_func_t hash_func;
    hash_cmp_func_t cmp_func;
};


static int BuildHashTableDlists(dlist_t **table, size_t arr_size)
{
    int failure_flag = 0;
    dlist_t *dlist = NULL;

    assert(NULL != table);

    if (arr_size == 0)
    {
        return 0;
    }

    dlist = DListCreate();
    
    if (NULL == dlist)
    {
        failure_flag = 1;
    }

    if (FAILURE != failure_flag)
    {
        table[arr_size - 1] = dlist;
        failure_flag = BuildHashTableDlists(table, arr_size - 1);
    }
    
    if (FAILURE == failure_flag)
    {
        DListDestroy(dlist);
        return FAILURE;
    }

    return SUCCESS;
}


hash_t *HashCreate(size_t size, 
                    hash_func_t user_hash_func, 
                    hash_cmp_func_t user_cmp_func)
{
    hash_t *hash_table = NULL;
    dlist_t **table = NULL;

    assert(NULL != user_hash_func);
    assert(NULL != user_cmp_func);
    assert(0 < size);

    hash_table = (hash_t *)malloc(sizeof(hash_t));
    if (NULL == hash_table)
    {
        return NULL;
    }

    table = (dlist_t **)malloc(size * POINTER_SIZE);
    if (NULL == table)
    {
        free(hash_table);
        return NULL;
    }

    if (FAILURE == BuildHashTableDlists(table, size))
    {
        free(table);
        free(hash_table);
        return NULL;
    }

    hash_table->table_size = size;
    hash_table->table = table;
    hash_table->hash_func = user_hash_func;
    hash_table->cmp_func = user_cmp_func;

    return hash_table;
}


void HashDestroy(hash_t *hash_table)
{
    size_t i = 0;

    assert(NULL != hash_table);

    for (i = 0; i < hash_table->table_size; ++i)
    {
        DListDestroy(hash_table->table[i]);
    }

    free(hash_table->table);
    free(hash_table);
}


static void *DListFindIMP(hash_t *hash_table, dlist_t *dlist, void *key)
{
    dlist_iter_t iter = NULL;
    dlist_iter_t end = NULL;
    
    assert(NULL != dlist);
    assert(NULL != hash_table);
    assert(NULL != key);

    iter = DListBegin(dlist);
    end = DListEnd(dlist);

    while (False == DListIsSameIterator(iter, end) &&
           IDENTICAL != hash_table->cmp_func(key, DListGetData(iter), NULL))
    {
        iter = DListNext(iter);
    }

    return iter;
}


int HashInsert(hash_t *hash_table, void *data)
{
    dlist_t *dlist = NULL;
    dlist_iter_t iter = NULL;
    size_t place = hash_table->hash_func(data) % hash_table->table_size;

    assert(NULL != hash_table);
    assert(NULL != data);
    
    dlist = hash_table->table[place];

    iter = DListPushFront(dlist, (const void *)data);
    if (True == DListIsSameIterator(iter, DListEnd(dlist)))
    {
        return FAILURE;
    }

    return SUCCESS;
}


void HashRemove(hash_t *hash_table, void *key)
{
    dlist_t *dlist = NULL;
    dlist_iter_t iter = NULL;

    assert(NULL != hash_table);
    assert(NULL != key);

    dlist = hash_table->table[hash_table->hash_func(key) % 
                              hash_table->table_size];
    
    iter = DListFindIMP(hash_table, dlist, key);
    if (True == DListIsSameIterator(iter, DListEnd(dlist)))
    {
        return;
    }

    DListErase(iter);
}


static dlist_iter_t HashFindOptimization(dlist_t *dlist, dlist_iter_t iter)
{
    void *data = NULL;
    dlist_iter_t new_iter = NULL;

    assert(NULL != dlist);
    assert(NULL != iter);

    data = DListGetData(iter);

    new_iter = DListPushFront(dlist, data);
    if (True == DListIsSameIterator(iter, DListEnd(dlist)))
    {
        return iter;
    }

    DListErase(iter);

    return new_iter;
}


void *HashFind(const hash_t *hash_table, void *key)
{
    dlist_t *dlist = NULL;
    dlist_iter_t iter = NULL;
    
    assert(NULL != hash_table);
    assert(NULL != key);

    dlist = hash_table->table[hash_table->hash_func(key) % 
                                       hash_table->table_size];


    iter = DListFindIMP((hash_t *)hash_table, dlist, key);
    
    if (True == DListIsSameIterator(iter, DListEnd(dlist)))
    {
        return NULL;
    }

    return DListGetData(HashFindOptimization(dlist, iter));
}


size_t HashSize(const hash_t *hash_table)
{
    size_t i = 0;
    int sum = 0;

    assert(NULL != hash_table);

    for (i = 0; i < hash_table->table_size; ++i)
    {
        sum += DListCount(hash_table->table[i]);
    }

    return sum;
}


int HashIsEmpty(const hash_t *hash_table)
{
    size_t i = 0;

    assert(NULL != hash_table);
    
    while (False == DListIsEmpty(hash_table->table[i]) && 
           i < hash_table->table_size - 1)
    {
        ++i;
    }

    return DListIsEmpty(hash_table->table[i]);
}


int HashForEach(const hash_t *hash_table, 
                hash_action_func_t action_func,
                void *action_func_param)
{
    size_t i = 0;
    dlist_iter_t start = NULL;
    dlist_iter_t end = NULL;
    int result = SUCCESS;

    assert(NULL != hash_table);
    assert(NULL != action_func);

    for (i = 0; i < hash_table->table_size; ++i)
    {
        if (False == DListIsEmpty(hash_table->table[i]))
        {
            start = DListBegin(hash_table->table[i]);
            end = DListEnd(hash_table->table[i]);
            result = DListForEach(start, end, action_func, action_func_param);
            if (FAILURE == result)
            {
                break;
            }
        }
    }

    return result;
}


double HashLoadFactor(const hash_t *hash_table)
{
    assert(NULL != hash_table);

    return HashSize(hash_table) / hash_table->table_size;
}


static double PowerTwo(double num)
{
    return num * num;
}


double HashVariance(const hash_t *hash_table)
{
    double lf = HashLoadFactor(hash_table);
    size_t i = 0;
    size_t sum = 0;
    double num = 0;

    assert(NULL != hash_table);

    for (i = 0; i < hash_table->table_size; ++i)
    {
        num = DListCount(hash_table->table[i]);
        sum += PowerTwo(num - lf);
    }

    return sum / hash_table->table_size;
}
