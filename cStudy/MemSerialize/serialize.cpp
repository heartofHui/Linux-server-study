/*************************************************************************
    > File Name: serialize.cpp
    > Author: chenhui
    > Mail: *********
    > Created Time: 2016年06月30日 22:25:52
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <memory>
#include "serialize.h"

void beNetData(int32_t& t)
{
	if (!isBigEndian())
	{
		char* c = (char*) &t;
		char temp = 0;
		temp = c[0];
		c[0] = c[3];
		c[3] = temp;

		temp = c[1];
		c[1] = c[2];
		c[2] = temp;
	}
}

void beNetData(int64_t& t)
{
	if(!isBigEndian())
	{
		char *c = (char *)&t;
		char temp = 0;
		temp = c[0];
		c[0] = c[7];
		c[7] = temp;

		temp = c[1];
		c[1] = c[6];
		c[6] = temp;

		temp = c[2];
		c[2] = c[5];
		c[5] = temp;

		temp = c[3];
		c[3] = c[4];
		c[4] = temp;
	}
}


void beNetData(float & t)
{
	if (!isBigEndian())
	{
		char* c = (char*) &t;
		char temp = 0;
		temp = c[0];
		c[0] = c[3];
		c[3] = temp;

		temp = c[1];
		c[1] = c[2];
		c[2] = temp;
	}
}

void beNetData(double& t)
{
	if(!isBigEndian())
	{
		char *c = (char *)&t;
		char temp = 0;
		temp = c[0];
		c[0] = c[7];
		c[7] = temp;

		temp = c[1];
		c[1] = c[6];
		c[6] = temp;

		temp = c[2];
		c[2] = c[5];
		c[5] = temp;

		temp = c[3];
		c[3] = c[4];
		c[4] = temp;
	}
}

bool reserve_space(Buffer* b, size_t bytes)
{
	if ((b->next + bytes) > b->size)
	{
		if (b->size >= MAX_BUFF_SIZE)
		{
			return false;
		}
		b->data = (char *)realloc(b->data, b->size * 2);
		b->size *= 2;
	}
	return true;
}

void MemSerialize(int32_t t,Buffer* b)
{
	beNetData(t);
	reserve_space(b, sizeof(int32_t));
	memcpy(b->data + b->next, &t, sizeof(int32_t));
	b->next += sizeof(int32_t);
}

void MemSerialize(int64_t t,Buffer* b)
{
	beNetData(t);
	reserve_space(b, sizeof(int64_t));
	memcpy(b->data + b->next, &t, sizeof(int64_t));
	b->next += sizeof(int64_t);
}

void MemSerialize(std::string s,Buffer* b)
{
	reserve_space(b, s.length());
	memcpy(b->data + b->next, &s, s.length());
	b->next += s.length();
}

void MemSerialize(char* s,Buffer* b)
{
	reserve_space(b,strlen(s));
	memcpy(b->data + b->next, s,strlen(s));
	b->next += strlen(s);
	//printf("len:%d\n",strlen(s));
}
