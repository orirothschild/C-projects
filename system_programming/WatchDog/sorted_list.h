#ifndef ILRD_SORTED_LIST_H
#define ILRD_SORTED_LIST_H

#include "dlist.h"

typedef dlist_iter_t srt_list_iter_t;
typedef struct srt_list srt_list_t;

typedef int (*srt_list_action_func_t)(void *node_data, void *param);
typedef int (*srt_list_is_match_func_t)(const void *node_data,
                                        const void *match_data,
                                        const void *param);
typedef int (*is_before_func_t)(const void *node_data, const void *user_data, 
                                void *param);


/*
* Create a sorted list with two terminators - head and tail.
* Return Value: a pointer to the created list, NULL if allocation failed
* Parameters  : -
* Input       : -
*/
srt_list_t *SortedListCreate(is_before_func_t sort_func);


/*
* Destroys the given sorted list
* Return Value: -
* Parameters  : srtlist: a sorted list
* Input       : -
*/
void SortedListDestroy(srt_list_t *srtlist);


/*
* Returns the first iterator in the given sorted list
* Return Value: an iterator for the sorted list
* Parameters  : srtlist: a sorted list
* Input       : srtlist cannot be NULL
*/
srt_list_iter_t SortedListBegin(const srt_list_t *srtlist);


/*
* Returns the end of the given sorted list
* Return Value: an iterator for the sorted list
* Parameters  : srtlist: a sorted list
* Input       : srtlist cannot be NULL
*/
srt_list_iter_t SortedListEnd(const srt_list_t *srtlist);


/*
* Returns the next iterator in the sorted list
* Return Value: Returns the next iterator in the sorted list
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case of performing this action on the 
                end of the list
*/
srt_list_iter_t SortedListNext(const srt_list_iter_t iter);


/*
* Returns the previous iterator in the sorted list
* Return Value: Returns the previous iterator in the sorted list
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case of performing this action on the
                beginning of the list
*/
srt_list_iter_t SortedListPrev(const srt_list_iter_t iter);


/*
* Checks whether the sorted list is empty
* Return Value: 1 if the list is empty, 0 otherwise
* Parameters  : srtlist: a sorted list
* Input       : srtlist cannot be NULL
*/
int SortedListIsEmpty(const srt_list_t *srtlist);


/*
* Counts the number of iterators in the list
* Return Value: Number of iterators
* Parameters  : srtlist: a sorted list
* Input       : srtlist cannot be NULL
*/
size_t SortedListSize(const srt_list_t *srtlist);


/*
* Checks whether the two iterators received are the same iterator
* Return Value: 1 if the iterators are the same, 0 otherwise
* Parameters  : iter1: the first iterator
                iter2: the second iterator
* Input       : both iterators cannot be NULL
*/
int SortedListIsSameIterator(srt_list_iter_t iter1, srt_list_iter_t iter2);

/*
* Inserts a iterator with the given data
* Return Value: the iterator that was inserted. If allocation failed, 
*               returns the end of the list
* Parameters  : srtlist: a sorted list
* Input       : sorted list cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR: data inserted must be same type as the data 
*               currently in the sorted list
*/
srt_list_iter_t SortedListInsert(srt_list_t *srtlist, const void *data,
                                void *param);


/*
* Erases the given iterator from sorted list
* Return Value: the next iterator after the given iterator
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR in case of given iterator being the previous
                iterator from the beginning or the end iterator of the list 
*/
srt_list_iter_t SortedListErase(srt_list_iter_t iter);


/*
* Retreives the data in the given iterator
* Return Value: a pointer to the data in the given iterator
* Parameters  : iter: the iterator
* Input       : iterator cannot be NULL
*/
void *SortedListGetData(const srt_list_iter_t iter);


/*
* Pops out the iterator from the beginning of the sorted list
* Return Value: - 
* Parameters  : srtlist: a sorted list
* Input       : srtlist cannot be NULL
*/
void SortedListPopFront(srt_list_t *srtlist);


/*
* Pops out the iterator from the end of the sorted list
* Return Value: - 
* Parameters  : srtlist: a sorted list
* Input       : srtlist cannot be NULL
*/
void SortedListPopBack(srt_list_t *srtlist);


/*
* Merges two sorted lists.
* Return Value: -
* Parameters  : dest: the sorted list into which the src list is merged
                src: the sorted which merged into the dest list
* Input       : dest, src cannot be NULL
*/
void SortedListMerge(srt_list_t *dest, srt_list_iter_t start, srt_list_iter_t end,
                     void *param);


/*
* Runs the given action function on the data of each iterator in the list
* between two given iterators
* Return Value: 0 if successful for each iterator in the list, 1 otherwise
* Parameters  : start: the beginning of the list of iterators to check
                end: the end of the list of iterators to check
                action_func: the function given to run on the data in the 
                             iterators with the given parameter
                param: the given parameter to run on the data with the 
                       action_func
* Input       : all inputs cannot be NULL
* NOTE        : UNDEFINED BEHAVIOUR: User cannot change the data using the 
*                                    action function
*/
int SortedListForEach(srt_list_iter_t start,
                      srt_list_iter_t end, 
                      srt_list_action_func_t action_func,
                      void *param);


/*
* Runs the given match function on the data of each iterator in the list between 
* two given iterators
* Return Value: 1 if a match was found, 0 otherwise
* Parameters  : start: the beginning of the list of iterators to check
                end: the end of the list of iterators to check
                match_func: the function given to run on the data in the
                            iterators with the given parameter
                param: the given parameter to run on the data with the 
                       match_func
* Input       : all inputs cannot be NULL
*/
int SortedListFind(srt_list_iter_t start,
                   srt_list_iter_t end, 
                   srt_list_is_match_func_t match_func, 
                   const void *param,
                   const void *match_data);


#endif
