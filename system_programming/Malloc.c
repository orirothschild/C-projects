#include <stdio.h>


int main ()
{
	char *str = NULL;

	


	return 0;
}


void *Malloc(size_t size)
{
	int protections = PROT_READ | PROT_WRITE;
	int flags = MAP_SHARED | MAP_ANON;

	return mmap(NULL, size, protections, flags, 0, 0);
}


void Free(void *ptr)
{

}
