/*************************************************************************
    > File Name: union.cpp
    > Author: chenhui
    > Mail: xxxxxx
    > Created Time: 2015年11月30日 10:45:52
 */
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
    void setVal(char * s)
    {
        content=s;
        len=strlen(s);
    }
};

union Data//
{
    int i;
    float f;
    struct TYPE_STRING str;//使用字符数组时注意越界
};

struct data_union
{
    int dataType;
    union Data uData;

    void setInt(int val)//c语言不支持在结构体中写函数，C++支持
    {
        //printf("set int\n");
        dataType=TYPE_INT;
        uData.i=val;
    }
    void setFloat(float val)
    {
        dataType=TYPE_FLOAT;
        uData.f=val;
    }
    void setString(char * val)
    {
        dataType=TYPE_STR;
        uData.str.setVal(val);
        //uData.str.content=val;
    }
};

void Print(struct data_union d)
{
    switch(d.dataType)
    {
        case TYPE_INT:
            printf("int:%d\n",d.uData.i);
            break;
        case TYPE_FLOAT:
            printf("float:%f\n",d.uData.f);
            break;
        case TYPE_STR:
            printf("strlen:%d\n",d.uData.str.len);
            printf("str:%s\n",d.uData.str.content);
            break;
        default:
            printf("unknown data type\n");
    }
}
int main(){

	struct data_union data;

	printf("Memory size occupied by data:%d\n",sizeof(data.uData));
    data.setInt(10);

	Print(data);
	char * s="asd";
	s="asdss";
	data.setString(s);
	Print(data);

	float f=12.33;
	data.setFloat(f);
	Print(data);
	return 0;
}
