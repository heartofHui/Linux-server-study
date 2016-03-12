/*************************************************************************
    > File Name: charstudy.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 3日 20:32:36
 ************************************************************************/
#include <stdio.h>
#include <string.h>

#define STR_MAX_LEN 16
int main()
{

	char c[STR_MAX_LEN];
	char p1[]="i love you very much!";
	char p2[]="123456789abcdefg";
	memset(&c,0,sizeof(c));	
	strncpy(c,p2,sizeof(c)-1);
	printf("c=%s\n",c);
	char m[20]="hello";
	//memset(m,0,sizeof(m));
	memmove(m+1,m,sizeof(m)-1);//内存地址重叠时，不能用memcpy
	printf("m=%s\n",m);

	char *cdup=strdup("iiiii");
	printf("cdup=%s\n",cdup);
	free(cdup);
	return 0;
}
