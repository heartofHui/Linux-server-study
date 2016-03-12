/*************************************************************************
    > File Name: func.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月23日  9:49:32
 ************************************************************************/
#include <stdio.h>
void Print(const char * str)
{
	printf("%s\n",str);
}

int main()
{
	void (*f)(const char *)=Print;

	f("hello");
	return 0;
}
