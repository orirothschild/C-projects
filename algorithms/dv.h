#ifndef ILRD_DYNAMIC_VECTOR_H
#define ILRD_DYNAMIC_VECTOR_H

typedef struct dynamic_vector vector_t;

/*
* Builds the dynamic vector
* Return Value: pointer to the dynamic vector, NULL if allocation failed
* Parameters  : size : the maximum number of elements within the dynamic vector
     		    element_size : the size of each element of the dynamic vector
* Proper Input: size >=0, element_size >= 0
* Time Complexity: O(1)
*/
vector_t *DVectorCreate(size_t size, size_t element_size);


/*
* Destroys the vector
* Return Value: -
* Parameters  : dv: the dynamic vector 
* Time Complexity: O(1)
*/
void DVectorDestroy(vector_t *dv);


/*
* Push the element into the next available space in the vector. If there is no
* available space, returns 0 for failure and does not push the data into the 
* vector
* Return Value: 0 for success, 1 for allocation failure
* Parameters  : dv: the dynamic vector
				element: the data to be added to the vector
* Proper Input: vector is not NULL, element is not NULL
* Time Complexity: O(n) @ worst case
* NOTE: On allocation failure, vector data is retained
*/
int DVectorPush(vector_t *dv, const void *element);


/*
* Pop the last element out from the vector
* Return Value: 0 for success, 1 for allocation failure
* Parameters  : dv: the dynamic vector
* Proper Input: vector is not NULL
* Time Complexity: O(n) @ worst case
* NOTE: On allocation failure, vector data is retained
*/
int DVectorPop(vector_t *dv);


/*
* Reserves a place in memory of size res_size
* Return Value: 0 for success, 1 for allocation failure
* Parameters  : dv: the dynamic vector
* Proper Input: vector is not NULL
* 				res_size > 0
* 				if reserve_size is less than size, new vector is size of current
* 				vector size
* Time Complexity: O(n) @ worst case
* NOTE: On allocation failure, vector data is retained
*/
int DVectorReserve(vector_t *dv, size_t reserve_size);


/*
* Returns the number of elements currently held by the vector
* Return Value: number of spaces asked for allocation by the user
* Parameters  : dv: the dynamic vector
* Proper Input: vector is not NULL
* Time Complexity: O(1)
*/
size_t DVectorSize(const vector_t *dv);


/*
* Returns the available space currently reserved by the vector
* Return Value: number of total spaces currently held by the vector
* Parameters  : dv: the dynamic vector
* Proper Input: vector is not NULL
* Time Complexity: O(1)
*/
size_t DVectorCapacity(const vector_t *dv);


/*
* Returns a pointer to the data at index idx in the vector
* Return Value: returns the a pointer to the data held at idx in the vector
* Parameters  : dv: the dynamic vector
* Proper input: idx >= 0 && idx <= size
				vector is not NULL
* Time Complexity: O(1)
* UNDEFINDED BEHAVIOUR: In case idx > capacity || idx < 0
* NOTE: If reallocation needed, addresses may change
*/
void *DVectorGetItemAddress(vector_t *dv, size_t idx);


#endif   /* ILRD_DYNAMIC_VECTOR_H */
