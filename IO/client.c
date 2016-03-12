#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>


#define BUFLEN 1024

int main(int argc,char ** argv)
{
	int sockfd;
	struct sockaddr_in s_addr;
	socklen_t len;
	char buf[BUFLEN];
	fd_set rfds;
	unsigned int port;
	struct timeval tv;
	int retval,maxfd;
	//create socket
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(errno);
	}
	else
	{
		printf("socket create sucess!\n");
	}
	//set server port
	if(argv[2])
		port=atoi(argv[2]);//switch string to int
	else
		port=4567;
	//set server ip
	bzero(&s_addr,sizeof(s_addr));
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(port);
	if(inet_aton(argv[1],(struct in_addr *)&s_addr.sin_addr.s_addr)==0)
	{
		perror(argv[1]);
		exit(errno);
	}
	//connect server
	if(connect(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(errno);
	}
	else
	{
		printf("connect success!\n");
	}
	while(1)
	{
		//clear the fd set
		FD_ZERO(&rfds);
		//add standard  fd to set
		FD_SET(0,&rfds);
		maxfd=0;
		FD_SET(sockfd,&rfds);
		if(maxfd<sockfd)
			maxfd=sockfd;
		//set expire dt
		tv.tv_sec=5;
		tv.tv_usec=0;
		//wait for chat
		retval=select(maxfd+1,&rfds,NULL,NULL,&tv);
		if(retval==-1)
		{
			printf("select wrong,client exit\n");
			break;
		}
		else if(retval==0)
		{
			printf("client input is null,and no server info reach,waiting.....\n");
			continue;
		}
		else
		{
			//server info coming
			if(FD_ISSET(sockfd,&rfds))
			{
				bzero(buf,BUFLEN);
				len=recv(sockfd,buf,BUFLEN,0);
				if(len>0)
					printf("server info:%s,length is:%d\n",buf,len);
				else
				{
					if(len<0)
						printf("receive fail\n");
					else
						printf("server quit\n");
					break;
				}
			}
			if(FD_ISSET(0,&rfds))
			{
				_retry:
				//send info
				bzero(buf,BUFLEN);
				//read from stream
				fgets(buf,BUFLEN,stdin);
				//print the info
				//fputs(buf,stdout);
				if(!strncasecmp(buf,"quit",4))
				{
					printf("client quit\n");
					break;
				}
				if(!strncmp(buf,"\n",1))
				{
					printf("please input again\n");
					goto _retry;
				}
				len=send(sockfd,buf,strlen(buf)-1,0);
				if(len>0)
				{
                    printf("\tinfo send success,and length:%d\n",len);
				}
				else
				{
					printf("info send fail\n");
					break;
				}
			}
		}

	}
	close(sockfd);
	return 0;
}
