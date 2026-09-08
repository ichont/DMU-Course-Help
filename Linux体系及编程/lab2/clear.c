#include <stdio.h>
int clear()
{
	printf("\033[2J");
	printf("\033[0;0H");
	return 0 ;
}
