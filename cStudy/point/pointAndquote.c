/*************************************************************************
    > File Name: pointAndquote.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 1日 14:56:21
 ************************************************************************/
#include <stdio.h>
void Print1(int * a);
void Print2(int& b);
int main()
{
	int a=10;
	Print1(&a);
	Print2(a);
	return 0;
}

void Print1(int * a)
{

	printf("Print1:%d\n",*a);
}

void Print2(int& b)
{
	printf("Print2:%d\n",a);
}
