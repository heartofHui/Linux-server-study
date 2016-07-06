#ifndef THREAD_LOCK
#define THREAD_LOCK

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

class ThreadLock
{
private:
	pthread_mutex_t* mutexPtr;
public:
	explicit inline ThreadLock(pthread_mutex_t *pm):mutexPtr(pm)//explicit 抑制隐式转换，inline加入符号表提高函数调用效率
	{
		//printf("lock of threadid:%d\n",pthread_self());//放在这里，打印出来的信息不准
		pthread_mutex_lock(mutexPtr);
		printf("lock of threadid:%d\n",pthread_self());
	}
	inline ~ThreadLock()
	{
		printf("unlock of threadid:%d\n",pthread_self());
		pthread_mutex_unlock(mutexPtr);
	}
};
//ThreadLock lock=&mutex;//如果不加explicit，可以这样写。

#endif
