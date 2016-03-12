/*************************************************************************
    > File Name: threadsync.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月29日 21:53:40
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

int count=0;

pthread_mutex_t count_mutex=PTHREAD_MUTEX_INITIALIZER;
void *addNum()
{
	int i=1;
	for(;i<=10000;i++)
	{
		pthread_mutex_lock(&count_mutex);//线程锁
		count+=i;
		printf("count:%d,of thread id:%d\n",count,pthread_self());
		pthread_mutex_unlock(&count_mutex);
	}
}

int main()
{
	pthread_t p1,p2;
	pthread_create(&p1,NULL,addNum,NULL);
	pthread_create(&p2,NULL,addNum,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	return 0;
}
/*
 * pthread_join使一个线程等待另一个线程结束。 代码中如果没有pthread_join主线程会很快结束从而使整个进程结束,
 * 从而使创建的线程没有机会开始执行就结束。
 * */
