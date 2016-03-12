/*************************************************************************
    > File Name: thread1.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年09月28日 20:53:36
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *thread(void * threadid)
{
	int tid;
	tid=(int)threadid;
	printf("hello world!it is me,thread%d\n",tid);
	pthread_exit(NULL);
}
int main(void)
{

	pthread_t id;
	void *ret;
	int i,retv;
	int t=123;
	retv=pthread_create(&id,NULL,(void *) thread,(void *)t);
	if(retv!=0)
	{
		printf("create pthread error\n");
		return 1;
	}
	for(i=0;i<10;i++)
	{
		printf("%d this is the main process\n",i);
	}
	pthread_join(id,&ret);
	printf("the thread return value is %d\n",(int)ret);
	return 0;
}
