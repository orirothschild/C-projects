#include <stdio.h>
#include <stdlib.h> /* system(), exit */


void PrintESC();
void PrintA();
void PrintB();
void PrintC();


int main()
{

	char ch = 0;
	int index = 0;


	
	while (1)
	{
		printf("please press a key and click 'enter':\n");
		system("stty -icanon -echo");
		ch = getchar();
		system("stty icanon echo");
		index = (int) ch;
		
		if (65 == index)
		{
			PrintA();
		}
		else if (66 == index)
		{
			PrintB();
		}
		else if (67 == index)
		{
			PrintC();
		}
		else if (27 == index)
		{
			PrintESC();
		}
	}
	
	return (0);
}





/* additional functions */
void PrintESC()
{
	printf("ESC was pressed\n\n");
	exit(0);
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
