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
		b->data = (unsigned char *)realloc(b->data, b->size * 2);
		b->size *= 2;
	}
	return true;
}

Buffer::Buffer()
{
	printf("construct\n");
	this->data = (unsigned char *)malloc(INI_BUFF_SIZE);
	memset(this->data, 0, INI_BUFF_SIZE);
	this->size = INI_BUFF_SIZE;
	this->next = 0;
}

Buffer::~Buffer()
{
	free(this->data);
	this->data = NULL;
}

Buffer::Buffer(Buffer& other)
{
	printf("copy construct\n");
	this->data = (unsigned char *) malloc(INI_BUFF_SIZE);
	memcpy(this->data, other.data, other.size);
	this->size = other.size;
	this->next = 0;
}

Buffer::Buffer(unsigned char * src, int32_t s)
{
	this->data = (unsigned char *)malloc(INI_BUFF_SIZE);
	memcpy(this->data, src, s);
	this->size = s;
	this->next = 0;
}

void MemSerialize(int32_t t, Buffer* b)
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

void MemSerialize(float t, Buffer* b)
{
	beNetData(t);
	reserve_space(b, sizeof(float));
	memcpy(b->data + b->next, &t, sizeof(float));
	b->next += sizeof(float);
}

void MemSerialize(double t, Buffer* b)
{
	beNetData(t);
	reserve_space(b, sizeof(double));
	memcpy(b->data + b->next, &t, sizeof(double));
	b->next += sizeof(double);
}

void MemSerialize(std::string s,Buffer* b)
{
	reserve_space(b, s.length());
	memcpy(b->data + b->next, &s, s.length());
	b->next += s.length();
}

void MemSerialize(char* s, Buffer* b)
{
	reserve_space(b, strlen(s));
	memcpy(b->data + b->next, s, strlen(s));
	b->next += strlen(s);
}

void MemDeseriaize(int32_t& t, Buffer& b, int32_t size)
{
	try{
		memcpy(&t, b.data + b.next, size);
		beNetData(t);
		b.next += size;
	} catch (...) {
		printf("catch exception\n");
	}
}

void MemDeseriaize(int64_t& t, Buffer& b, int32_t size)
{
	try{
		memcpy(&t, b.data + b.next, sizeof(size));
		beNetData(t);
		b.next += size;
	}catch(...)
	{
		printf("catch exception\n");
	}
}

void MemDeseriaize(char* s, Buffer& b, int32_t size)
{
	try{
		memcpy(s, b.data + b.next, sizeof(size));
		b.next += size;
	}catch(...)
	{
		printf("catch exception\n");
	}
}
