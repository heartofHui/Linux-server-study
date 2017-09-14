#include <iostream>
#include<sys/time.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

void *ttt(void *);
sem_t sem;

int main()
{
	pthread_t t_a;
	sem_init(&sem, 0, 0);
	pthread_create(&t_a, NULL, ttt, NULL);
	cout << "begin\n";
	int n;
	for (;;)
	{
		cin >> n;
		if (n == 1)
		{
			sem_post(&sem);//信号量+1
		}
	}

	pthread_join(t_a, NULL); //wait a_b thread end
	cout << "exit\n";
	sem_destroy(&sem);
	return 0;
}

//时间a的值增加ms毫秒
void timeraddMS(struct timeval *a, uint ms)
{
    a->tv_usec += ms * 1000;
    if(a->tv_usec >= 1000000)
    {
        a->tv_sec += a->tv_usec / 1000000;
        a->tv_usec %= 1000000;
    }
}

void *ttt(void *data)
{
	struct timeval now;
	struct timespec outtime;
	while (1)
	{
		int ret;
		gettimeofday(&now, NULL);
		cout << now.tv_sec << " " << (now.tv_usec) << "\n";
		timeraddMS(&now, 1500);
		outtime.tv_sec = now.tv_sec;
		outtime.tv_nsec = now.tv_usec * 1000;
		ret = sem_timedwait(&sem, &outtime);
		if (ret == -1)
		{
			gettimeofday(&now, NULL);
			cout << "sem_timewait timeout " << now.tv_sec << " "
					<< (now.tv_usec) << "\n\n";
		}
		else
		{
			cout << "sem_timewait ok\n";
			break;
		}
		sleep(1);
	}
	return 0;
}
