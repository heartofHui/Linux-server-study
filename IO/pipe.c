/*************************************************************************
    > File Name: pipe.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年09月17日 12:16:44
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	int result=-1;
	int fd[2],nbytes;
	pid_t pid;
	char string[]="hello world!\0";
	char readbuf[100];
	int *write_fd=&fd[1];
	int *read_fd=&fd[0];
	result=pipe(fd);
	if(result==-1)
	{

		printf("Pipe create error\n");
		exit(1);
	}
	pid=fork();
	if(pid==-1)
	{

		printf("fork create error\n");
		exit(1);
	}
	if(pid==0)
	{
		close(*read_fd);
		result=write(*write_fd,string,strlen(string));
		printf("write %d bytes\n",result);
		return 0;
	}
	else
	{
		close(*write_fd);
		nbytes=read(*read_fd,readbuf,sizeof(readbuf));
		printf("the parent received %d bytes of data:%s",nbytes,readbuf);
		

	}
	return 0;

}
