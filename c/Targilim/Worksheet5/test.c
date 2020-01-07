#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadStdin();
enum messages {OK, Error, StrTooLong};
int RemoveFile(char *str, char *filename);
int ExitProg(char *str, char *filename);
int AppendComp(char *str, char *input);
int AppendStrToFile(char *str, char *filename);
int WriteStrToFile(char *str, char *filename);
void CopyFiles(char *file_dest, char *file_src);
int CountFileRows(char *str, char *filename);

int main(int argc, char **argv)
{
	char *filename = argv[1];
	char *buff = 0;
	char *cmpstr = "<remove";
	
	(void) argc;
	(void) argv;

	
	
	
	ReadStdin(&buff);
	printf("the sting was: %s\n", buff);
	
	
	if (0 == AppendComp(cmpstr, buff))
	{
		printf("same\n");
	}
	else
	{
		printf("different\n");
	}

	
/*	RemoveFile(buff, filename);  */
	
/*	ExitProg(buff, filename);  */
	
/*	AppendStrToFile(buff, filename); */
	
	

	WriteStrToFile(buff, filename);
	
/*	CountFileRows(buff, filename); */
	
	
	return (0);
}


int CountFileRows(char *str, char *filename)
{
	int row_num = 0;
	char ch = 0;
	FILE *file_ptr = 0;
	(void)str;
	
	file_ptr = fopen(filename, "r");
	if (NULL == file_ptr)
	{
		perror("There was a problem opening the file");
		exit(Error);
	}
	
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
	printf("There were %d rows in the file %s\n.", row_num, filename);
	return (row_num);
}




int WriteStrToFile(char *str, char *filename)
{
	FILE *file_ptr = fopen(filename, "r+");
	FILE *temp_file = fopen("temp_file", "a+");
		

	fputs(str, temp_file);
	fputc('\n', temp_file);
	
	fclose(file_ptr);
	fclose(temp_file);

	CopyFiles("temp_file", filename);

	remove(filename);
	
	CopyFiles(filename, "temp_file");

	return (OK);
}


void CopyFiles(char *file_dest, char *file_src)
{
	char buffer[81] = {0};
	size_t buff_size = 80;
	char *line = 0;
	
	FILE *dest = fopen(file_dest, "a+");
	FILE *src = fopen(file_src, "r+");
	
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
	
	fclose(src);
	fclose(dest);
}

int AppendStrToFile(char *str, char *filename)
{
	FILE *file_ptr = fopen(filename, "w+");
	
	++str;
	
	fputs(str, file_ptr);
	fputc('\n', file_ptr);
	
	fclose(file_ptr);
	
	return (OK);
}


int AppendComp(char *str, char *input)
{
	(void)str;
	if ('<' == *input)
	{
		return (OK);
	}

	return (Error);
}


int ExitProg(char *str, char *filename)
{
	(void) str;
	(void) filename;
	
	printf("You chose to exit the program\n");
	free(str);
	exit(OK);
}

int RemoveFile(char *str, char *filename)
{
	int status = 0;
	(void)str;
	
	status = remove(filename);
	
	if (0 == status)
	{
		printf("File deleted successfully\n");
	}
	else
	{
		perror("There was a problem deleting the file\n");
		exit(Error);
	}
	
	return (OK);
}


int ReadStdin(char **buffer)
{
	size_t buff_size = 80;
	int len = 0;
	
	
	*buffer = (char *)malloc(buff_size * sizeof(char));
    if(NULL == buffer)
    {
        perror("Unable to allocate buffer");
        exit(Error);
    }
	
	printf("Please input a string (up to 79 characters):\n");
	
	if(fgets(*buffer, buff_size, stdin) == NULL )
	{
		perror("There was a problem reading from STDIN");
		exit(Error);
	}
	
	printf("the sting was: %s\n", *buffer);
	
	len = strlen(*buffer);
	*(*buffer+len-1) = '\0';

	return (OK);
}
