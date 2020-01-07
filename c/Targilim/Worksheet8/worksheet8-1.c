#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <assert.h> /* asserts */

#define ARR_SIZE 3
#define STR_SIZE 50

typedef struct Processor
{
	void *data;
	void (*Add)(void *add, void **data);
	void (*Print)(void *to_print);
	void (*FreeMemory)(void *data);
} pro;


/* Addition to the existing data using ints*/
static void AddInt(void *add, void **data);

/* Addition to the existing data using floats */
static void AddFloat(void *add, void **data);

/* Addition to the existing string by concatenation */
static void AddStr(void *add, void **data);

/* Prints the data saved as an int */
static void PrintInt(void *to_print);

/* Prints the data saved as a float */
static void PrintFloat(void *to_print);

/* Prints the data saved as a string */
static void PrintStr(void *to_print);

/* Free malloced memory */
static void FreeMemory(void *data);

/* Empty function, does nothing */
static void Empty(void *data);

/* Check the allocation */
static CheckAlloc(void *data)

int main()
{
	enum messages {INT, FLOAT, STR};

	int i = 5;
	float f = 35.58;
	char *data_str = "hello";
	char *add_str = "there";
	int p = 3;

	pro proc_arr[ARR_SIZE];
	
	/* initialized the array of structs */
	*(int *)&proc_arr[INT].data = i;
	proc_arr[INT].Add = AddInt;
	proc_arr[INT].Print = PrintInt;
	proc_arr[INT].FreeMemory = Empty;
	
	*(float *)&proc_arr[FLOAT].data = f;
	proc_arr[FLOAT].Add = AddFloat;
	proc_arr[FLOAT].Print = PrintFloat;
	proc_arr[FLOAT].FreeMemory = Empty;
	
	*(char **)&proc_arr[STR].data = NULL; 
	proc_arr[STR].Add = AddStr;
	proc_arr[STR].Print = PrintStr;
	proc_arr[STR].FreeMemory = FreeMemory;

	/* Use the functions to add and print for each data type */	
	proc_arr[INT].Add(&p, &proc_arr[INT].data);
	proc_arr[INT].Print(&proc_arr[INT].data);
	
	proc_arr[FLOAT].Add(&f, &proc_arr[FLOAT].data);
	proc_arr[FLOAT].Print(&proc_arr[FLOAT].data);
		
	proc_arr[STR].data = (char *)malloc(strlen(data_str) + 1);
	CheckAlloc(proc_arr[STR].data);
	strcpy(proc_arr[STR].data, data_str);
	proc_arr[STR].Add(add_str, &proc_arr[STR].data);
	proc_arr[STR].Print(*(char **)&proc_arr[STR].data);
	proc_arr[STR].FreeMemory(proc_arr[STR].data);

	return (0);
}


/* Aditional Functions */
static void AddInt(void *add, void **data)
{
	assert(NULL != add);
	assert(NULL != data);
	
	*(int *)data = *(int *)data + *(int *)add;
}

static void PrintInt(void *to_print)
{
	assert(NULL != to_print);
	
	printf("The int is: %d\n", *(int *)to_print);
}


static void AddFloat(void *add, void **data)
{
	assert(NULL != add);
	assert(NULL != data);
	
	*(float *)data += *(float *)add;
}

static void PrintFloat(void *to_print)
{
	assert(NULL != to_print);
	
	printf("The float is: %f\n", *(float *)to_print);
}


static void AddStr(void *add, void **data)
{
	assert(NULL != add);
	assert(NULL != data);
	
	*((char **)data) = (char *)realloc(*data, 
	strlen((char *)data) + strlen(add) + 1);
	
	if (NULL == data)
	{
		perror("There was an error during reallocation");
		exit(0);
	}
	
	strcat((char *)(*data), (char *)add);
}


static void PrintStr(void *to_print)
{
	printf("The string is: %s\n", (char *)to_print);
}


static void FreeMemory(void *to_free)
{
	free(to_free);
}


static void Empty(void *data)
{
	(void)data;
}


static CheckAlloc(void *data)
{
	if (NULL == data)
	{
		perror("There was an error during reallocation");
		exit(0);
	}
}
