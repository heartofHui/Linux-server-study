/*************************************************************************
    > File Name: pointAndArr.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 1日 20:50:05
 ************************************************************************/
#include <stdio.h>

int main()
{
	int a[5]={1,2,3,4,5};
	int * p=&a[0];
	int i=0;
	for(;i<5;i++)
	{
		printf("%d\n",*p);
		p++;
	}
	return 0;		
}
