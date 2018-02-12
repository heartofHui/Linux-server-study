/*
 * freelockqueue.cpp
 *
 *  Created on: 2018年1月17日
 *      Author: Administrator
 */
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>

using namespace std;

struct DataType_STRING
{
    char* mpContent;
	int  miLength;
};

boost::lockfree::queue<int, boost::lockfree::fixed_sized<false> > RecoverQueue(1280);

void *consume(void*)
{
	int tmp = 0;
	while(1)
	{
		if(RecoverQueue.empty())
		{
			continue;
		}
		RecoverQueue.pop(tmp);
		//cout<<"pop = "<< tmp<<endl;
	}
}

void *product(void*)
{
	uint32_t i = 0;
	while(1)
	{
		RecoverQueue.push(i++);
		//usleep(1);
	}
}

int main()
{
//	bool succ = false;
//	for(int i = 0;i<1290;i++)
//	{
//		succ = RecoverQueue.push(i);
//		//usleep();
//		cout<<succ<<endl;
//	}
//	int tmp = 0;
//	for(int i = 0;i<1290;i++)
//	{
//		RecoverQueue.pop(tmp);
//		cout<<tmp<<endl;
//	}

	pthread_t p1,p2,p3;
	pthread_create(&p1,NULL,consume,NULL);
	pthread_create(&p2,NULL,consume,NULL);
	pthread_create(&p3,NULL,product,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	return 0;
}

//g++ freelockqueue.cpp -o free -lboost_system

