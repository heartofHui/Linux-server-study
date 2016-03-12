/*************************************************************************
    > File Name: sizeoftest.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 3日 11:48:39
 ************************************************************************/
#include <stdio.h>
int main()
{
	char c[10];
	char d[10];
	memset(&c,0,sizeof(c));
	memset(&d,'\0',sizeof(d));
	printf("%d\n",sizeof(c));
	printf("%d\n",sizeof(d));
	return 0;
}
