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
		
		switch(index)
		{
			case 27 :
				PrintESC();
				break;
			case 65 :
				PrintA();
				break;
			case 66 :
				PrintB();
				break;
			case 67 :
				PrintC();
				break;
			default :
				printf("Try Again\n");
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
