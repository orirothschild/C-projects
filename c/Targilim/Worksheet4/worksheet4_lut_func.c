#include <stdio.h>
#include <stdlib.h> /* system(), exit */

static void *FuncTable(int index, void (**func_ptr)());
void message(void (*func)());
void PrintESC();
void Printa();
void Printb();
void Printc();
void PrintA();
void PrintB();
void PrintC();
void Empty();

int main()
{

	char ch = 0;
	int index = 0;
	void (*func_ptr)() = 0;

	
	while (1)
	{
		printf("please press a key and click 'enter':\n");
		system("stty -icanon -echo");
		ch = getchar();
		system("stty icanon echo");
		index = (int) ch;
		
		FuncTable(index, &func_ptr);
		
		message(func_ptr);
	}
	
	return (0);
}





/* additional functions */
void message(void (*func)())
{
	func();
}


static void *FuncTable(int index, void (**func_ptr)())
{
	static void (*func_table[256])() = {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
										Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, PrintESC, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, PrintA, PrintB, PrintC, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Printa, Printb, Printc,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
									 	Empty, Empty, Empty, Empty, Empty, Empty
									 };
	*func_ptr = func_table[index];
}

void PrintESC()
{
	printf("ESC was pressed\n\n");
	exit(0);
}

void Printa()
{
	printf("a was pressed\n\n");
}

void Printb()
{
	printf("b was pressed\n\n");
}

void Printc()
{
	printf("c was pressed\n\n");
}

void PrintA()
{
	printf("A was pressed\n\n");
}

void PrintB()
{
	printf("B was pressed\n\n");
}

void PrintC()
{
	printf("C was pressed\n\n");
}
void Empty()
{
	printf("Try Again\n");
}
