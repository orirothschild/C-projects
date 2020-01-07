/* RC7 */
#ifndef ILRD_HASHT_H
#define ILRD_HASHT_H

#include <stddef.h> /* size_t */


typedef struct hash_table hash_t;

typedef size_t (*hash_func_t)(void *key);
typedef int (*hash_cmp_func_t)(const void *user_data, const void *table_data,
                                void *param);
typedef int (*hash_action_func_t)(void *table_data, void *param);

/* 
struct hash_table
{
    size_t table_size;
    dlist_t **table;
    hash_func_t hash_func;
    hash_cmp_func_t cmp_func;
};

 */
/*
* Creates a hash table with the given size and hash function
* Return Value: a pointer to the hash table
* Parameters  : size : the size of the table
                user_hash_func: the given user hash function - parameters: 
                                                               void *key
                cmp_func: a given compare func
* Input       : size cannot be 0
                user_hash_func cannot be NULL
                cmp_func cannot be NULL
* Time Complexity: O(n)
*/
hash_t *HashCreate(size_t size, 
                   hash_func_t user_hash_func, 
                   hash_cmp_func_t cmp_func);


/*
* Destroys the hash table. User must be aware that data is not [free()]'d in the 
* proccess.
* Return Value: - 
* Parameters  : hash_table: a hash table.
* Input       : hash_table cannot be NULL.
* Time Complexity: O(n)
*/
void HashDestroy(hash_t *hash_table);


/*
* Inserts the given data into the given hash table; hash table is open hash
* / closed address.
* Return Value: 0 if inserted, 1 otherwise
* Parameters  : hash_table: a hash table
                data: the user data
* Input       : both cannot be NULL
* Time Complexity: O(1)
*/
int HashInsert(hash_t *hash_table, void *data);


/*
* Removes the given data from the hash table, 
* Return Value: -
* Parameters  : hash_table: a hash table
                key: the user key
* Input       : both cannot be NULL
* NOTES       : Error handling: In case user asks to remove data that no longer
                                exists in the table, continue.
* Time Complexity: O(1)
*/
void HashRemove(hash_t *hash_table, void *key);


/*
* Finds the key in the hash table, and returns a pointer to it.
* Return Value: a pointer to the key in the hash table, NULL if the data is 
                not present 
* Parameters  : hash_table: a hash table
                key: the user key
* Input       : both cannot be NULL
*  Time Complexity: O(1)
*/
void *HashFind(const hash_t *hash_table, void *key);


/*
* Performs the action func on each data point in the hash table, until it had
* been applied to every data point or until the function returns error status 1.
* Return Value: 0 if successfully performed on all data points, 1 otherwise
* Parameters  : hash_table: a hash table
                action_func: a user action function - receives the data from 
                                                      the table and a user
                                                      parameter
                action_func_param: a parameter given by the user
* Input       : hash_table and action_func cannot be NULL
*  Time Complexity: O(n)
*/
int HashForEach(const hash_t *hash_table, 
                hash_action_func_t action_func,
                void *action_func_param);


/*
* Returns the number of data points currently in the hash table
* Return Value: the amount of data
* Parameters  : hash_table: a hash table
* Input       : hash_table cannot be NULL
*  Time Complexity: O(n)
*/
size_t HashSize(const hash_t *hash_table);


/*
* Calculates the load factor of the hash table.
* Return Value: the load factor
* Parameters  : hash_table: a hash table
* Input       : hash_table cannot be NULL
 Time Complexity: O(n)
*/
double HashLoadFactor(const hash_t *hash_table);


/*
* Checks whether the hash table is empty
* Return Value: 1 if empty, 0 otherwise
* Parameters  : hash_table: a hash table
* Input       : hash_table cannot be NULL
 Time Complexity: O(n)
*/
int HashIsEmpty(const hash_t *hash_table);


/*
* Calculates the variance of the hash table
* Return Value: the variance of the table
* Parameters  : hash_table: a hash table
* Input       : hash_table cannot be NULL
 Time Complexity: O(n)
*/
double HashVariance(const hash_t *hash_table);


#endif   /* ILRD_HASHT_H */
