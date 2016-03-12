/*************************************************************************
    > File Name: main.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月22日 14:56:12
 ************************************************************************/
#include <stdio.h>
#include "stack/stack.h"
//extern void push(char);
//extern char pop();
//extern int is_empty();
//extern int top;//不是变量定义，不会分配内存空间
int a,b=1;

int main()
{
	push('a');
	push('v');
	push('i');

	while(!is_empty())
	{
		putchar(pop());
	}
	putchar('\n');
//	printf("%d\n",top);
	return 0;
}
