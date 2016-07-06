/*************************************************************************
    > File Name: big_little_endian.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月14日 15:28:00
 ************************************************************************/
#include <stdio.h>

int main()
{
	int32_t i=1;
	if((*(char *) & i)==0)
	{
		printf("big\n");
	}
	else
	{
		printf("little\n");
	}
	return 0;
}
