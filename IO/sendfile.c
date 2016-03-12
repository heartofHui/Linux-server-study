/*************************************************************************
    > File Name: sendfile.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年09月22日 11:13:07
 ************************************************************************/
#include <unistd.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sendfile.h>
int main(int argc,char * argv[])
{

	if(argc<3)
	{
		printf("usage:%s ip_address port_number filename\n",argv[0]);
		return 1;
	}
	const char * ip=argv[1];
	int port=atoi(argv[2]);//atoi()把字符串型转成整型
	const char * file_name=argv[3];
	int filefd=open(file_name,O_RDONLY);
	assert(filefd>0);
	struct stat stat_buf;
	fstat(filefd,&stat_buf);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));

	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);
	
	int sock=socket(AF_INET,SOCK_STREAM,0);
	assert(sock>=0);
	int ret=bind(sock,(struct sockaddr *)& address,sizeof(address));
	assert(ret!=-1);
	ret=listen(sock,5);

	assert(ret!=-1);

	struct sockaddr_in client;
	socklen_t client_addrlength=sizeof(client);
	int connfd=accept(sock,(struct sockaddr *)&client,&client_addrlength);
	if(connfd<0)
	{
		printf("errno is :%d\n",errno);
	}
	else

	{
		sendfile(connfd,filefd,NULL,stat_buf.st_size);
		close(connfd);
	}
	close(sock);
	return 0;

}

//sendfile函数在两个文件描述符之间传递数据（完全在内核中操作），
//从而避免了内核缓冲区和用户缓冲区之间的数据拷贝，效率很高，
//称为零拷贝。
