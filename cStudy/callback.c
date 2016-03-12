/*************************************************************************
    > File Name: callback.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月19日  0:20:00
 ************************************************************************/
#include <stdio.h>

void sayHello(int i)
{
	printf("hello%d\n",i);
}

void sayBye(int i)
{
	printf("bye%d\n",i);
}

void callback(int times,void (* excute)(int))
{
	int i;
	for(i=0;i<times;i++)
	{
		excute(i);
	}

}

int main()
{
	callback(2,sayHello);
	callback(4,sayBye);
	return 0;
}
