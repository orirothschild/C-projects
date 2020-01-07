#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit */
#include <string.h> /* strings */
#include <assert.h> /* asserts */

#define ELEMENTS 10
#define NAMELEN 50

struct DateOfBirth
{
	size_t day;
	size_t month;
	size_t year;
};

struct Contact
{
	struct DateOfBirth dob;
	size_t ID;
	char f_name[NAMELEN];
	char l_name[NAMELEN];
};

/* Writes an array of structs to a file (in binary) */
static void WriteStructsToFile(char *filename, struct Contact *con_arr);

/* Reads an array of structs from a file and assigns to an array */ 
static void ReadStructFromFile(char *filename, struct Contact *read_arr);

/* Prints the members of a struct */
static void PrintStruct(struct Contact *print_struct);

/* Checks that a file openned correctly */
static void CheckFile(FILE *file);


int main(int argc, char **argv)
{
	char *filename = argv[1];
	enum {John, Paul, Ringo, George, Steven, Joe, David, Mick, Bob, Jim};
	
	struct Contact con_arr[ELEMENTS] = {0};
	struct Contact read_arr[ELEMENTS] = {0};
	
	(void)argc;
	if (NULL == filename)
	{
		filename = "_temp_file_";
	}

	con_arr[John].dob.day = 9;
	con_arr[John].dob.month = 10;
	con_arr[John].dob.year = 1940;	
	con_arr[John].ID = 10001;
	strcpy(con_arr[John].f_name, "John");
	strcpy(con_arr[John].l_name, "Lennon");
	
	con_arr[Paul].dob.day = 18;
	con_arr[Paul].dob.month = 6;
	con_arr[Paul].dob.year = 1942;	
	con_arr[Paul].ID = 10002;
	strcpy(con_arr[Paul].f_name, "Paul");
	strcpy(con_arr[Paul].l_name, "McCartney");
	
	con_arr[Ringo].dob.day = 7;
	con_arr[Ringo].dob.month = 7;
	con_arr[Ringo].dob.year = 1940;	
	con_arr[Ringo].ID = 10003;
	strcpy(con_arr[Ringo].f_name, "Ringo");
	strcpy(con_arr[Ringo].l_name, "Starr");
	
	con_arr[George].dob.day = 25;
	con_arr[George].dob.month = 2;
	con_arr[George].dob.year = 1943;	
	con_arr[George].ID = 10004;
	strcpy(con_arr[George].f_name, "George");
	strcpy(con_arr[George].l_name, "Harrison");
	
	con_arr[Steven].dob.day = 26;
	con_arr[Steven].dob.month = 3;
	con_arr[Steven].dob.year = 1948;	
	con_arr[Steven].ID = 10005;
	strcpy(con_arr[Steven].f_name, "Steven");
	strcpy(con_arr[Steven].l_name, "Tyler");
	
	con_arr[Joe].dob.day = 10;
	con_arr[Joe].dob.month = 9;
	con_arr[Joe].dob.year = 1950;	
	con_arr[Joe].ID = 10006;
	strcpy(con_arr[Joe].f_name, "Joe");
	strcpy(con_arr[Joe].l_name, "Perry");
	
	con_arr[David].dob.day = 8;
	con_arr[David].dob.month = 1;
	con_arr[David].dob.year = 1947;	
	con_arr[David].ID = 10007;
	strcpy(con_arr[David].f_name, "David");
	strcpy(con_arr[David].l_name, "Bowie");
	
	con_arr[Mick].dob.day = 26;
	con_arr[Mick].dob.month = 7;
	con_arr[Mick].dob.year = 1943;	
	con_arr[Mick].ID = 10008;
	strcpy(con_arr[Mick].f_name, "Mick");
	strcpy(con_arr[Mick].l_name, "Jagger");
	
	con_arr[Bob].dob.day = 6;
	con_arr[Bob].dob.month = 2;
	con_arr[Bob].dob.year = 1945;	
	con_arr[Bob].ID = 10009;
	strcpy(con_arr[Bob].f_name, "Bob");
	strcpy(con_arr[Bob].l_name, "Marley");
	
	con_arr[Jim].dob.day = 8;
	con_arr[Jim].dob.month = 12;
	con_arr[Jim].dob.year = 1943;	
	con_arr[Jim].ID = 10010;
	strcpy(con_arr[Jim].f_name, "Jim");
	strcpy(con_arr[Jim].l_name, "Morrison");
	

	WriteStructsToFile(filename, con_arr);
	ReadStructFromFile(filename, read_arr);
	PrintStruct(&read_arr[John]);
	PrintStruct(&read_arr[Paul]);
	PrintStruct(&read_arr[Ringo]);
	PrintStruct(&read_arr[George]);
	PrintStruct(&read_arr[Steven]);
	PrintStruct(&read_arr[Joe]);
	PrintStruct(&read_arr[David]);
	PrintStruct(&read_arr[Mick]);
	PrintStruct(&read_arr[Bob]);
	PrintStruct(&read_arr[Jim]);
	
	return (0);
}


static void WriteStructsToFile(char *filename, struct Contact *con_arr)
{
	FILE *file = fopen(filename, "w+");
	
	assert(NULL != filename);
	assert(NULL != con_arr);
	
	CheckFile(file);

	fwrite(con_arr, sizeof(struct Contact), ELEMENTS, file);

	fclose(file);
}


static void ReadStructFromFile(char *filename, struct Contact *read_arr)
{
	FILE *file = fopen(filename, "r");
	
	assert(NULL != filename);
	assert(NULL != read_arr);
	
	CheckFile(file);
	
	fread(read_arr, sizeof(struct Contact), ELEMENTS, file);
	
	fclose(file);
}


static void PrintStruct(struct Contact *print_struct)
{
	assert(NULL != print_struct);
	
	printf("First name: %s\n", print_struct->f_name);
	printf("Last name: %s\n", print_struct->l_name);
	printf("ID name: %lu\n", print_struct->ID);
	printf("Day: %lu\n", print_struct->dob.day);
	printf("Month: %lu\n", print_struct->dob.month);
	printf("Year: %lu\n", print_struct->dob.year);
	printf("\n");
}


static void CheckFile(FILE *file)
{
	if (NULL == file)
	{
		perror("there was a problem opening the file\n");
		exit(0);
	}
}
