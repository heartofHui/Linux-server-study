/*************************************************************************
    > File Name: epolloneshot.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 2日 14:52:35
 ************************************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds
{
	int epollfd;
	int sockfd;
};

int setnonblocking(int fd)
{
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}
void addfd(int epollfd,int fd,bool oneshot)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN | EPOLLET;
	if(oneshot)
	{
		event.events |= EPOLLONESHOT;
	}
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}

void reset_oneshot(int epollfd,int fd)
{
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}

void * worker(void * arg)
{
	int sockfd=((fds*)arg)->sockfd;
	int epollfd=((fds*)arg)->epollfd;
	printf("receive data of sockfd:%d\n",sockfd);
	char buffer[BUFFER_SIZE];
	memset(&buffer,'\0',sizeof(buffer));
	while(1)
	{
		int ret=recv(sockfd,buffer,sizeof(buffer),0);
		if(ret==0)
		{
			close(sockfd);
			printf("client closed socket\n");
			break;
		}
		else if(ret>0)
		{
			printf("receive data buffer:%s\n",buffer);
			//sleep(4);
		}
		else
		{
			if(errno==EAGAIN)
			{
			
				reset_oneshot(epollfd,sockfd);
				printf("read later\n");
				break;
			}
			//printf("receive data error\n");
			//break;
		}
		memset(&buffer,'\0',sizeof(buffer));
	}
	printf("end thread receiving data on fd:%d\n",sockfd);
}
int main(int argc,char * argv[])
{
	if(argc<=2)
	{
		printf("usage:%s ip_address port_number\n",argv[0]);
		return 1;
	}
	const char * ip=argv[1];
	int port=atoi(argv[2]);
	int ret=0;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );
	int listenfd=socket(PF_INET,SOCK_STREAM,0);
	assert( listenfd >= 0 );
	ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
	assert( ret != -1 );

	ret = listen( listenfd, 5 );
	assert( ret != -1 );
	
	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd=epoll_create(5);
	
	assert(epollfd!=-1);
	addfd(epollfd,listenfd,false);
	int i=0;
	while(1)
	{
		int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
		if(ret<0)
		{
			printf("epoll failure\n");
			break;
		}
		for(i=0;i<ret;i++)
		{
			int sockfd=events[i].data.fd;
			if(sockfd==listenfd)//add clientfd to epoll when connect
			{
			    printf("add sockfd into epoll\n");
				struct sockaddr_in client_address;
				socklen_t client_addrlen=sizeof(client_address);
				int connfd=accept(listenfd,(struct sockaddr*)& client_address,&client_addrlen );
				addfd(epollfd,connfd,true);
			}
			else if(events[i].events & EPOLLIN)//create a thread to deal it when client info come
			{
			    printf("create thread to deal\n");
				pthread_t thread;
				fds fds_new_work;
				fds_new_work.epollfd=epollfd;
				fds_new_work.sockfd=sockfd;
				pthread_create(&thread,NULL,worker,(void *)&fds_new_work);
			}
			else
			{
				printf("something else happend\n");
			}
		}
	}
	close(listenfd);
	return 0;
}
