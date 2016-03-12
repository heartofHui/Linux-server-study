/*************************************************************************
    > File Name: safestr.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 1日 22:46:12
 ************************************************************************/
#include <stdio.h>
#include <string.h>
int main()
{

	char s[]="i love you";
	char c[10];
	memset(&c,0,sizeof(c));
	strncpy(c,s,sizeof(c)-1);
	printf("%s\n",c);
	return 0;
}
