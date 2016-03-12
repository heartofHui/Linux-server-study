/*************************************************************************
    > File Name: enum.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年01月31日 15:47:26
 ************************************************************************/
#include <stdio.h>
int main()
{
	enum{
		DEF_INT=0,
		DEF_STR,
		DEF_FLOAT
	};
	printf("int is %d\n",DEF_INT);
	printf("string is %d\n",DEF_STR);
	return 0;
}
