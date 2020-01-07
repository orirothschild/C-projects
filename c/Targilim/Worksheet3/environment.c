#include <stdio.h>   /* standard */
#include <stdlib.h>	 /* malloc */
#include <string.h>	 /* strlen */
#include <ctype.h>	 /* tolower() */

static char *StrLwr(char *str);
static void PrintDataStructure(int env_counter, char **data_structure);
static void FreeFunc(int allocation_counter, char **new_data_structure, 
					 char **new_data_structure_start);




int main (int argc, char *argv[], char **envp)
{

	int i = 0;
	int env_counter = 0;
	int alloc_counter = 0;
	char **new_data_structure = 0;
	char **new_data_structure_start = 0;
	char **new_data_structure_end = 0;
	char **env_var = envp;
	char *temp = 0;
	
	

	
	/* count number of ENVIRONMENT variables */	
	while (0 != *env_var)
	{
		++env_counter;
		++env_var;
	}
	
	env_var = envp;
	

	/* build new data structure for array of pointers to string */
	new_data_structure = (char **)malloc(sizeof(char *) * (env_counter + 1));
	new_data_structure_start = new_data_structure;
	

	/* get length needed for malloc for each string, then malloc and move on */
	env_var = envp;
	
	for (i = 0; i < env_counter; i++)
	{
		
		temp = (char *)malloc((strlen(*env_var) + 1)*sizeof(char));

		/* test */
		if (20 == alloc_counter)
		{
			temp = NULL;
			
		}

		


		/* if malloc fails, free all the memory that has been allocated 
		for the strings, free array of strings, exit status 1 */ 		
		if (NULL == temp)
		{
			
			new_data_structure--;
			FreeFunc(alloc_counter, new_data_structure, new_data_structure_start);
			exit(1);
		}
		
		

		strcpy(temp ,*env_var);
		
		temp = StrLwr(temp);
		
		*new_data_structure = temp;

		++new_data_structure;
		++env_var;
		++alloc_counter;
	}
	
	/* hold the end location */
	new_data_structure_end = new_data_structure;

	/* move new data structure to beginning */
	new_data_structure = new_data_structure_start;


	/* print new data structure */
	PrintDataStructure(env_counter, new_data_structure);

	
	new_data_structure = new_data_structure_end - 1;
	FreeFunc(alloc_counter, new_data_structure, new_data_structure_start);
	

	return (0);
}





static void FreeFunc(int allocation_counter, char **new_data_structure, 
					 char **new_data_structure_start)
{
	int i = 0;

	for (i = 0; i < allocation_counter; i++)
	{
		free(*new_data_structure);
		--new_data_structure;
	}
	new_data_structure = new_data_structure_start;
	free(new_data_structure);
}




static char *StrLwr(char *str)
{

	char *runner = str;
	
	while(*runner)
	{
		*runner = tolower(*runner);
		++runner;
	}

	return (str);
}




static void PrintDataStructure(int env_counter, char **data_structure)
{
	int i = 0;

	for (i = 0; i < env_counter; i++)
	{
		printf("print func the environment variable is %s\n", *data_structure);
		++data_structure;
	}

	printf("\n");
}

