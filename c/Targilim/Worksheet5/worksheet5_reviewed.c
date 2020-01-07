#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */


#define ARR_SIZE 5

enum messages {OK, Error, StrTooLong};

int ReadStdin(char **buffer);
int RemoveFile(const char *str, const char *filename);
int CountFileRows(const char *str, const char *filename);
int ExitProg(const char *str, const char *filename);
int AppendStrToFile(const char *str, const char *filename);
int WriteStrToFile(const char *str, const char *filename);
void CopyFiles(const char *file_dest, const char *file_src);
int AppendComp(const char *str, const char *input);
int WriteComp(const char *str1, const char *str2);



int main(int argc, char **argv)
{
	char *buff = 0;
	int i = 0;
	char *filename = argv[1];
	enum processors {remove, count, exit, append, write};
	
	/* Define the struct processor and array */
	struct processor 
	{
		char *cmd;
		int (*comp_func)(const char *cmd, const char *str);
		int (*oper_func)(const char *str, const char *filename);
	};
	struct processor proc_arr[ARR_SIZE];
	
	assert(NULL != filename);
	(void) argc;
	
	proc_arr[remove].cmd = "-remove";
	proc_arr[remove].comp_func = strcmp;
	proc_arr[remove].oper_func = RemoveFile;
	
	proc_arr[count].cmd = "-count";
	proc_arr[count].comp_func = strcmp;
	proc_arr[count].oper_func = CountFileRows;

	proc_arr[exit].cmd = "-exit";
	proc_arr[exit].comp_func = strcmp;
	proc_arr[exit].oper_func = ExitProg;

	proc_arr[append].cmd = "<";
	proc_arr[append].comp_func = AppendComp;
	proc_arr[append].oper_func = AppendStrToFile;

	proc_arr[write].comp_func = WriteComp;
	proc_arr[write].oper_func = WriteStrToFile;

	
	
	while (1)
	{
		ReadStdin(&buff);
		i = 0;

		while (i < ARR_SIZE)
		{
			if (proc_arr[i].comp_func(proc_arr[i].cmd, buff) == OK)
			{
				proc_arr[i].oper_func(buff, filename);
				break;
			}
			++i;
		}
	}
	
	return (0);
}


/* Additional Functions */
int RemoveFile(const char *str, const char *filename)
{
	int status = 0;
	
	assert(NULL != filename);
	assert(NULL != str);
	
	(void)str;
	
	status = remove(filename);
	
	return (OK);
}


int CheckFile(FILE *file_ptr)
{
	if (NULL == file_ptr)
	{
		perror("There was a problem opening the file.");
		exit(Error);
	}

	return (OK);
}


int CountFileRows(const char *str, const char *filename)
{
	int row_num = 0;
	char ch = 0;
	FILE *file_ptr = fopen(filename, "r");
	
	assert(NULL != filename);
	assert(NULL != str);	
	
	(void)str;
	
	CheckFile(file_ptr);
	
	do
	{
		ch = fgetc(file_ptr);
		if ('\n' == ch)
		{
			++row_num;
		}
		if (feof(file_ptr))
		{
			break;
		}
	}
	while (EOF != ch);
		
	fclose(file_ptr);
	printf("There were %d rows in the file %s.\n", row_num, filename);
	return (row_num);
}


int ExitProg(const char *str, const char *filename)
{
	assert(NULL != filename);
	assert(NULL != str);
	
	(void) str;
	(void) filename;
	
	printf("You chose to exit the program\n");
	free((char *)str);
	exit(OK);
}


int WriteComp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);	
	
	(void) str1;
	(void) str2;
	return (0);
}


int WriteStrToFile(const char *str, const char *filename)
{
	FILE *file_ptr = fopen(filename, "a+");
	
	assert(NULL != filename);
	assert(NULL != str);
	
	CheckFile(file_ptr);
	
	/* start copying from the second character */
	++str;
	
	fputs(str, file_ptr);
	fputc('\n', file_ptr);
	
	fclose(file_ptr);
	
	return (OK);
}


int AppendComp(const char *str, const char *input)
{
	assert(NULL != input);
	assert(NULL != str);
	
	(void)str;
	if ('<' == *input)
	{
		return (OK);
	}

	return (Error);
}


int AppendStrToFile(const char *str, const char *filename)
{
	FILE *file_ptr = fopen(filename, "a+");
	FILE *temp_file = fopen("temp_file", "a+");
	
	assert(NULL != filename);
	assert(NULL != str);	
	
	CheckFile(file_ptr);	
	
	fputs(str, temp_file);
	fputc('\n', temp_file);
	
	/* closed the files before sending to helper function becuase it opens them
	again */
	fclose(file_ptr);
	fclose(temp_file);

	CopyFiles("temp_file", filename);
	remove(filename);
	CopyFiles(filename, "temp_file");
	remove("temp_file");

	return (OK);
}


void CopyFiles(const char *file_dest, const char *file_src)
{
	char buffer[81] = {0};
	size_t buff_size = 80;
	char *line = 0;
	FILE *dest = fopen(file_dest, "a+");
	FILE *src = fopen(file_src, "r+");

	assert(NULL != file_dest);
	assert(NULL != file_src;
	
	CheckFile(dest);
	CheckFile(src);
	
	do
	{
		line = fgets(buffer, buff_size, src);

		if(NULL == line)
		{
			break;
		}
		
		fputs(buffer, dest);	
	}
	while (NULL != line);
	
	fclose(dest);
	fclose(src);
}

int ReadStdin(char **buffer)
{
	
	size_t buff_size = 80;
	int len = 0;
	
	assert(NULL != buffer);	
	
	*buffer = (char *)malloc(buff_size * sizeof(char));
    if(NULL == buffer)
    {
        perror("Unable to allocate buffer");
        exit(Error);
    }
	
	printf("Please input a string (up to 79 characters):\n");
	
	if(NULL == fgets(*buffer, buff_size, stdin))
	{
		perror("There was a problem reading from STDIN");
		exit(Error);
	}

	printf("the sting was: %s\n", *buffer);
	
	len = strlen(*buffer);
	*(*buffer+len-1) = '\0';

	return (OK);
}

