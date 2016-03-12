/*************************************************************************
    > File Name: deamon.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月20日 18:40:45
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void daemonize()
{
	pid_t pid;

	if((pid=fork())<0)
	{
		perror("fork");
		exit(1);
	}else if(pid!=0)
		exit(0);
	setsid();

	if(chdir("/")<0)//chdir() change current work path
	{
		perror("chdir");
		exit(1);
	}
	dup2(0,1);
	dup2(0,2);
}

int main()
{

	daemonize();
	while(1);
}
