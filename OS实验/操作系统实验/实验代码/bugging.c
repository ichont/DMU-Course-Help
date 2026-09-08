#include <stdio.h>
static char buff[256];
static char* string;
int main ()
{
	printf("Please:");
	gets(string);
	printf("\nYour is %s\n",string);
}
