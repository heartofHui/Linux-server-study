/*************************************************************************
    > File Name: forktest.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月18日 10:15:53
 ************************************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid=fork();//创建子进程
    char *msg=NULL;//防止野指针
    if(pid<0)
    {
        printf("error\n");
    }
    if(pid==0)
    {
        msg="child process\n";
        printf("this is child");
    }
    else
    {
        msg="parent process\n";
        printf("this is parent");
    }
    int i=0;
    for(;i<10;i++)
    {
        printf(msg);
        sleep(1);
    }
    return 0;
}