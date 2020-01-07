#include <stdio.h>
#include <stdlib.h> /* system(), exit */


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
	



	
	while (1)
	{
		/* turn off terminal buffering, get input, turn on terminal buffering */
		printf("please press a key and click 'enter':\n");
		system("stty -icanon -echo");
		ch = getchar();
		system("stty icanon echo");
		
		/* turn the char input into an index for the function pointer table */
		index = (int) ch;
		
		/* call message function with function pointer */
		message(func_table[index]);
	}
	
	return (0);
}





/* additional functions */
void message(void (*func)())
{
	func();
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
