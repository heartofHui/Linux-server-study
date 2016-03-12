/*************************************************************************
    > File Name: strncpy.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月24日 11:47:21
 ************************************************************************/
#include <stdio.h>
#include <string.h>
int main()
{
    printf("strncpy的用法\n");
	char s[5]="sssss";
	char *p="abcdefghijk";
	//strcpy(s,p);
	memset(&s,0,sizeof(s));
	printf("sizeof:%d\n",sizeof(s));//输出5
	strncpy(s,p,sizeof(s)-1);


	printf("%s\n",s);
	printf("snprintf的用法\n");

    char *p1="123456789";
	int n=snprintf(s,sizeof(s),p1);//不能用sprintf会溢出
	printf("s:%s src len:%d\n",s,n);


    printf("strnlen的用法\n");
    //s[4]='d';
    printf("%d\n",strnlen(s,6));
	return 0;
}
/*
char *strncpy(char *dest, const char *src, size_t n);
src串的长度应该小于dest缓冲区的大小，且n为dest缓冲区的大小减1或者更小，
即至少留出一个位置给'\0'。（如果src串的长度大于或等于dest缓冲区的大小，
则n应该为dest缓冲区的大小减1或者更小，否则将溢出。）


int snprintf(char *str, size_t size, const char *format, ...);
说明：最多从源串中拷贝(size - 1)个字符到目标串中，再在后面加一个'/0'。


size_t strnlen(const char *s, size_t maxlen);
说明：获取字符串s中的字符个数n，不包括结尾的'/0'；如果n <= maxlen，则返回n，否则返回maxlen。
*/