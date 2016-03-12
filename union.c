/*************************************************************************
    > File Name: union.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年11月30日 10:45:38
 ******************************************************************/
#include <stdio.h>
#include <string.h>

enum
{
    TYPE_INT=1,
    TYPE_FLOAT,
    TYPE_STR
};

struct TYPE_STRING//自定义字符串
{
    int len;
    char * content;
//    void setStr(char * s)
//    {
//        content=s;
//        len=strlen(s);
//    }
};

union Data
{
    int i;
    float f;
    struct TYPE_STRING str;//使用字符数组时注意越界
};

struct data_union
{
    int dataType;
    union Data uData;
};

void Print(struct data_union d)
{
    switch(d.dataType)
    {
        case TYPE_INT:
            printf("data:%d\n",d.uData.i);
            break;
        case TYPE_FLOAT:
            printf("data:%f\n",d.uData.f);
            break;
        case TYPE_STR:
            printf("data:%s\n",d.uData.str.content);
            break;
        default:
            printf("unknown data type\n");
    }
}
int main(){
	
	struct data_union data;

	printf("Memory size occupied by data:%d\n",sizeof(data.uData));

	data.dataType=TYPE_INT;
	data.uData.i=10;
	Print(data);

	return 0;
}


//共用体是一种特殊的数据类型，允许在相同的位置存储不同的数据类型。可以定义一个带有多成员的共用体，但是任何时候只有一个成员带有值。
//共用体占用内存应足够存储共用体中最大成员。
