/*************************************************************************

    > File Name: threadsync.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月29日 21:53:40
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "threadLock.h"

int64_t count=0;
int64_t count2=0;

int atomic_mutex = 0;
int lock = 0;
int unlock = 1;

pthread_mutex_t count_mutex=PTHREAD_MUTEX_INITIALIZER;
void *addNum(void*)//.c文件时没加void*,可以编译运行。.cpp文件时编译不过（pthread_create(,,addNum,)）提示类型转换无效
{
	int i=1;
	for(;i<=400000;i++)
	{
		ThreadLock lock(&count_mutex);
		count+=i;
	}
}

void *addNum2(void*)
{
	int i=1;
	for(;i<=400000;i++)
	{
		CASFreeLock casLock(atomic_mutex,lock,unlock);
		count2+=i;
	}
}

int64_t getSystemTimeMs()
{
    struct timeval timeNow;
    gettimeofday(&timeNow, NULL);
    return timeNow.tv_sec*1000 + timeNow.tv_usec/1000;
}

int main()
{
	int64_t timeStart,timeEnd;
	timeStart = getSystemTimeMs();
	pthread_t p1,p2,p3,p4;
	pthread_create(&p1,NULL,addNum,NULL);
	pthread_create(&p2,NULL,addNum,NULL);
	pthread_create(&p3,NULL,addNum,NULL);
	pthread_create(&p4,NULL,addNum,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);

	timeEnd = getSystemTimeMs();
	printf("thread lock->count:%lld, time use=%lldms\n",count, (timeEnd-timeStart));
	timeStart = getSystemTimeMs();
	pthread_create(&p1,NULL,addNum2,NULL);
	pthread_create(&p2,NULL,addNum2,NULL);
	pthread_create(&p3,NULL,addNum2,NULL);
	pthread_create(&p4,NULL,addNum2,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	timeEnd = getSystemTimeMs();
	printf("cas lock free->count2:%lld, time use=%lldms\n",count2, (timeEnd-timeStart));

	return 0;
}
/*
 * pthread_join使一个线程等待另一个线程结束。 代码中如果没有pthread_join主线程会很快结束从而使整个进程结束,
 * 从而使创建的线程没有机会开始执行就结束。
 * */
/*run:
 * g++ threadsync.cpp -o threadcas
 * ./threadcas.exe or ./threadcas
 * */
