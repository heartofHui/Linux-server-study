/*************************************************************************
    > File Name: fcntl.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年09月26日  5:22:25
 ************************************************************************/
//file control对文件描述符的各种操作
#include <unistd.h>
#include <stdio.h>
int main()
{
	uid_t uid=getuid();//unsigned int 
	uid_t euid=geteuid();
	printf("userid is %d ,effective user_id is %d\n",uid,euid);
	return 0;
}
