/*************************************************************************
    > File Name: pointAndTwoArr.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 1日 21:06:18
 ************************************************************************/
#include <stdio.h>

int main()
{
	int a[2][2]={
		{
			1,2
		},
		{
			3,4
		}
	};
	int (*p)[2];
	p=&a[0];
	int i=0,j=0;
	for(;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%d\n",*(*(p+i)+j));
		}
	}
	//printf("%d\n",*(*(p+1)+1));
	return 0;
}
