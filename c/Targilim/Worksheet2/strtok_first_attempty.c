/* returns a pointer to the last token when called with NULL or reinitializes
 with a new str when given. */
char *StrToken(char *str, const char *delim)
{
	
	



	/* declare static variables*/
	static char *latest_token_ptr;
	char *return_ptr;
	char *temp_ptr;

	
	
	/*if first time, static variable so that it keeps the value over consequtive
	calls, else, static variable already has the data from previous call */
	if (str)
	{
		latest_token_ptr = str;

	}
	if (!latest_token_ptr)
	{
		/* return NULL; */
		return '\0';
	}


	/* return pointer gets location of latest token pointer */
	return_ptr = latest_token_ptr;


	/* find the location of the first delimiter, and replace the value with 
	'\0' */
	while (delim)
	{
		latest_token_ptr = StrCharacter(return_ptr, *delim);
		if (!latest_token_ptr)
		{
			++delim;
		}
		else
		{
			break;
		}
	}
	/* latest_token_ptr = StrCharacter(return_ptr, *delim); */
	if (!latest_token_ptr)
	{	
		return return_ptr;
	}


	/* pass to temp holder */
	temp_ptr = latest_token_ptr;	


	/* increment latest_toke_ptr, used in the next round; */
	++latest_token_ptr;


	/* turn previous pointer placement to null */
	*temp_ptr = '\0';

	return (return_ptr);


	
}
