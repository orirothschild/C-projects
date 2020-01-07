#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <errno.h>  /* errno */

#include "c_buffer.h" /* ADT */

#define RUN_TEST(test) (!test) ? printf("FAIL : " #test"\n" ) : printf("PASS : " #test"\n")

int TestCBufferCreate();
int TestCBufferFreeSpace1();
int TestCBufferIsEmpty1();
int TestCBufferIsEmpty2();
int TestCBufferWrite1();
int TestCBufferWrite2();
int TestCBufferWrite3();
int TestCBufferWrite4();
int TestCBufferWrite5();
int TestCBufferRead1();
int TestCBufferRead2();
int TestCBufferRead3();
int TestCBufferRead4();
int TestCBufferRead5();

enum {FAIL, PASS};

int main()
{
	RUN_TEST(TestCBufferCreate());
	RUN_TEST(TestCBufferFreeSpace1());
	RUN_TEST(TestCBufferIsEmpty1());
	RUN_TEST(TestCBufferIsEmpty2());	
	RUN_TEST(TestCBufferWrite1());
	RUN_TEST(TestCBufferWrite2());
	RUN_TEST(TestCBufferWrite3());
	RUN_TEST(TestCBufferWrite4());
	RUN_TEST(TestCBufferWrite5());	
	RUN_TEST(TestCBufferRead1());
	RUN_TEST(TestCBufferRead2());
	RUN_TEST(TestCBufferRead3());
	RUN_TEST(TestCBufferRead4());
	RUN_TEST(TestCBufferRead5());
		
	return (0);
}


int TestCBufferCreate()
{
	size_t i = 5;
	c_buffer_t *cb = CBufferCreate(i);

	if (NULL != cb)
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferFreeSpace1()
{
	size_t i = 5;
	
	c_buffer_t *cb = CBufferCreate(i);
	
	if (5 == CBufferFreeSpace(cb))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferIsEmpty1()
{
	size_t i = 5;
	
	c_buffer_t *cb = CBufferCreate(i);
	
	if (1 == CBufferIsEmpty(cb))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferIsEmpty2()
{
	size_t i = 5;
	int len = 0;
	char string[30] = {0};
	char str2[30] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	
	if (1 == CBufferIsEmpty(cb))
	{
		CBufferDestroy(cb);
		return (PASS);
	}	
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferWrite1()
{
	size_t i = 5;
	int k = 3;
	
	c_buffer_t *cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, &k, sizeof(int));
	
	if (16 == CBufferFreeSpace(cb))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferWrite2()
{
	size_t i = 5;
	int k = 4;
	
	c_buffer_t *cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, &k, sizeof(int));
	++k;
	CBufferWrite(cb, &k, sizeof(int));
	
	if (12 == CBufferFreeSpace(cb))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferWrite3()
{
	size_t i = 5;
	int k = 4;
	
	c_buffer_t *cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, &k, sizeof(int));
	++k;
	CBufferWrite(cb, &k, sizeof(int));
	++k;
	CBufferWrite(cb, &k, sizeof(int));
	++k;
	CBufferWrite(cb, &k, sizeof(int));
	++k;
	CBufferWrite(cb, &k, sizeof(int));
	++k;
	if (-1 == CBufferWrite(cb, &k, sizeof(int)))
	{
		CBufferDestroy(cb);
		/* print out the error */
		perror("Error");
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferWrite4()
{
	size_t i = 5;
	int len = 0;
	char string[30] = {0};
	char str2[30] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	
	
	if (0 == strcmp(str2, "blerg"))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferWrite5()
{
	int len = 0;
	char string[30] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(22);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);	
	CBufferWrite(cb, string, len);	
	
	if (2 == CBufferWrite(cb, string, len))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferRead1()
{
	size_t i = 5;
	int len = 0;
	char string[30] = {0};
	char str2[30] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	
	
	if (len == CBufferRead(cb, str2, len))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferRead2()
{
	size_t i = 5;
	int len = 0;
	char string[30] = {0};
	char str2[30] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);		
	
	if (-1 == CBufferRead(cb, str2, len))
	{
		CBufferDestroy(cb);
		/* print out the error */
		perror("Error");
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferRead3()
{
	size_t i = 5;
	int len = 0;
	char string[30] = {0};
	char str2[30] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(i * sizeof(int));
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	
	if (15 == CBufferFreeSpace(cb))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferRead4()
{
	int len = 0;
	char string[20] = {0};
	char str2[20] = {0};
	char str3[5] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(22);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str3, len);
	
	if (0 == strcmp("blerg", str3))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}


int TestCBufferRead5()
{
	int len = 0;
	char string[20] = {0};
	char str2[20] = {0};
	c_buffer_t *cb = NULL;
	strcpy(string, "blerg");
	len = strlen(string); /* 5 */
	
	cb = CBufferCreate(20);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferWrite(cb, string, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);
	CBufferRead(cb, str2, len);	

	
	if (5 == CBufferRead(cb, str2, 6))
	{
		CBufferDestroy(cb);
		return (PASS);
	}
	CBufferDestroy(cb);
	
	return (FAIL);
}

