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
		//printf("lock of threadid:%d\n",pthread_self());
	}
	inline ~ThreadLock()
	{
		//printf("unlock of threadid:%d\n",pthread_self());
		pthread_mutex_unlock(mutexPtr);
	}
};

class CASFreeLock
{
private:
	int* mutex;
	int* lock;
	int* unlock;
public:
	explicit inline CASFreeLock(int& m, int& l, int& u)
	{
		mutex = &m;
		lock = &l;
		unlock = &u;
		//printf("mutex:%d,lock:%d,unlock:%d\n",*mutex,*lock,*unlock);

		while(!__sync_bool_compare_and_swap(mutex, *lock, 1))
		{
			usleep(100000);//sleep 10ms
		}
	}
	inline ~CASFreeLock()
	{
		//printf("~mutex:%d,lock:%d,unlock:%d\n",*mutex,*lock,*unlock);
		__sync_bool_compare_and_swap(mutex, *unlock, 0);

	}
};

#endif
