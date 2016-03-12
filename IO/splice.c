/*************************************************************************
    > File Name: splice.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年09月22日 12:02:28
 ************************************************************************/
//splice函数用于在两个文件秒速符之间移动数据,可以用来实现回射服务器
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char * argv[])
{

	if(argc<=2)
	{
		printf("usage :%s ip_address port_number\n",basename(argv[0]));
		return 1;
	}
	const char * ip=argv[1];
	int port=atoi(argv[2]);
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sock=socket(AF_INET,SOCK_STREAM,0);
	assert(sock>=0);
	int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));

	assert(ret!=-1);
	ret=listen(sock,5);
	struct sockaddr_in client;
	socklen_t client_addrlength=sizeof(client);
	int connfd=accept(sock,(struct sockaddr*)&client,&client_addrlength);

	if(connfd<0)
	{
		printf("errno is:%d\n",errno);
	}
	else
	{
		int pipefd[2];
		ret=pipe(pipefd);
		//将connfd上流入的客户端数据定向到管道中
		ret=splice(connfd,NULL,pipefd[1],NULL,32768,/*SPLICE_F_MORE|SPLICE_F_MOVE*/ 5);
		assert(ret!=-1);
		//将管道的输出定向到connfd客户端连接文件描述符
		ret=splice(pipefd[0],NULL,connfd,NULL,32768,/*SPLICE_F_MORE|SPLICE_F_MOVE*/ 5);
		assert(ret!=-1);
		close(connfd);
	}
	close(sock);
	return 0;
}
//我们通过splice函数将客户端的内容读入到pipefd[1]中，然后利用splice函数从
//pipefd[0]中读出内容到客户端，从而实现了简单高效的回射服务。整个过程未执
//行recv和send操作，因此也未涉及空间和内核空间之间的数据拷贝
