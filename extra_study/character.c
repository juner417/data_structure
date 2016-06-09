#include <stdio.h>

int main()
{
	char a[] = "hello world";
	char* p = a;
	while ( *p != 0)
	{
		printf("%c\n", *p); 
		p++;
	}
}
