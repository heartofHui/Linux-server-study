/*************************************************************************
    > File Name: mmap.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年09月21日 15:53:33
 ************************************************************************/
#include <sys/mman.h>
#include <sys/types.h> /* for open */
#include <sys/stat.h> /* for open */
#include <fcntl.h>     /* for open */
#include <unistd.h>    /* for lseek and write */
//所有打开的文件都有当前文件偏移量（current file offset）
//lseek可以改变文件的cfo
#include <stdio.h>
#include <string.h>
int main(int argc,char ** argv)
{
	int fd;
	char * map_mem,*p;
	int flen=1024;
	void * start_addr=0;
	fd=open(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

	flen=lseek(fd,1,SEEK_END);
	write(fd,"\0",1);//在文件最后添加空字符，便于printf正常工作
	lseek(fd,0,SEEK_SET);
	start_addr=0x80000;
	//允许读，允许其他进程访问
	map_mem=mmap(start_addr,flen,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("%s\n",map_mem);
	//strstr(string,search)返回str2在str1中首次出现的物理内存地址
	while((p=strstr(map_mem,"hello")))
	{
		memcpy(p,"Linux",5);
		p+=5;
	}
	close(fd);
	munmap(map_mem,flen);
	return 0;

}
