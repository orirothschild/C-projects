#include <stdio.h>   /* standard */
#include <stdlib.h>	 /* malloc */
#include <string.h>	 /* strlen */
#include <ctype.h>	 /* tolower() */

static char *StrLwr(char *str);
static void PrintDataStructure(int env_counter, char **data_structure);
static void FreeFunc(int allocation_counter, char **new_data_structure, 
					 char **new_data_structure_start);
static int CountEnvVars(char **env_var);
static int BuildStrings(int env_counter, char **env_vars, 
						   char **data_struct, char **data_struct_start);



int main (int argc, char *argv[], char **envp)
{

	
	int env_counter = 0;
	int alloc_counter = 0;
	char **new_data_struct = 0;
	char **new_data_struct_start = 0;
	char **new_data_struct_end = 0;
	char **env_vars = envp;
	
	
	env_counter = CountEnvVars(env_vars);
	
	/* print new data structure */
	PrintDataStructure(env_counter, env_vars);
	
	new_data_struct = (char **)malloc(sizeof(char *) * (env_counter + 1));
	new_data_struct_start = new_data_struct;
	alloc_counter = BuildStrings(env_counter, env_vars, new_data_struct, new_data_struct_start);
	
	/* hold the end location */
	new_data_struct_end = new_data_struct_start + env_counter;

	/* move new data structure to beginning */
	new_data_struct = new_data_struct_start;


	/* print new data structure */
	PrintDataStructure(env_counter, new_data_struct);

	
	new_data_struct = new_data_struct_end - 1;
	FreeFunc(alloc_counter, new_data_struct, new_data_struct_start);
	

	return (0);
}








/*  additional functions  */
static int CountEnvVars(char **env_vars)
{
	int env_counter = 0;
	
	while (0 != *env_vars)
	{
		++env_counter;
		++env_vars;
	}

	return (env_counter);
}



static int BuildStrings(int env_counter, char **env_vars, 
						char **new_data_struct, char **new_data_struct_start)
{
	int i = 0;
	int alloc_counter = 0;
	char *temp = 0;
	
	for (i = 0; i < env_counter; i++)
	{
		
		temp = (char *)malloc((strlen(*env_vars) + 1)*sizeof(char));
			
		if (NULL == temp)
		{
			--new_data_struct;
			FreeFunc(alloc_counter, new_data_struct, new_data_struct_start);
			exit(1);
		}
		

		*new_data_struct = StrLwr(strcpy(temp ,*env_vars));
	
		++new_data_struct;
		++env_vars;
		++alloc_counter;
	
		
	}
	
	return alloc_counter;
}



static void FreeFunc(int allocation_counter, char **new_data_struct, 
					 char **new_data_struct_start)
{
	int i = 0;

	for (i = 0; i < allocation_counter; i++)
	{
		free(*new_data_struct);
		--new_data_struct;
	}
	new_data_struct = new_data_struct_start;
	free(new_data_struct);
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




static void PrintDataStructure(int env_counter, char **data_struct)
{
	int i = 0;

	for (i = 0; i < env_counter; i++)
	{
		printf("print func the environment variable is %s\n", *data_struct);
		++data_struct;
	}

	printf("\n");
}

