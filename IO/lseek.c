
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd,size,len;
	char * buf="hello!i am writing to file!";
	char buf_r[10];
	len=strlen(buf);
	if((fd=open("b.txt",O_CREAT|O_TRUNC|O_RDWR,0666))<0)
	{
		perror("open:error");
		exit(1);
	}
	else
	{
		printf("open file b.txt %d\n",fd);

	}
	if((size=write(fd,buf,len))<0)
	{
		perror("write error");
		exit(1);
	}
	lseek(fd,0,SEEK_SET);
	if((size=read(fd,buf_r,15))<0)
	{
		perror("read error");
		exit(1);
	}
	else
	{
		printf("read from file:%s\n",buf_r);
		if(close(fd)<0)
		{
			perror("close error");
			exit(1);

		}
		else
		{

			printf("close b.txt");
			exit(0);
		}
	}
}
