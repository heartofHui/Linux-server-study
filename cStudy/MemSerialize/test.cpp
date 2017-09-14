#include <iostream>
#include <string>
#include <stdio.h>
#include "serialize.h"
#include "struct/UserInfoStruct.h"

using namespace std;

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef long long			int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int 		uint32;
typedef unsigned long long  uint64;

typedef unsigned char 		BYTE;


void printBufferHex(unsigned char * buff, int32_t size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%02X", buff[i]);
	}
	printf("\n");
}

void printfBuffer(Buffer* buffer)
{
	for(int i = 0;i< buffer->size;i++)
	{
		printf("%02X", buffer->data[i]);
	}
	printf("\n");
}

int main()
{
	UserInfo uInfo;
	uInfo.age = 2;
	uInfo.height = 100;
	strcpy(uInfo.name.s, "chen");
	uInfo.name.len = strlen(uInfo.name.s);

	Buffer* buff = new Buffer();
	uInfo.pack(buff);
	//printBufferHex(buff->data, buff->next);
	cout << "buff size:"<<buff->next << endl;

	unsigned char buf[1024] = { 0 }; // = buff->data;
	memcpy(buf, buff->data, buff->next);
	//printBufferHex(buf, buff->next);
	int32_t size = buff->next;
	Buffer psBuf(buf, size);
	//printBufferHex(psBuf.data, psBuf.size);

	printfBuffer(&psBuf);

	UserInfo *recvUser = new UserInfo;
	recvUser->unpack(psBuf);
	recvUser->dump();
	printf("%d,%d\n",psBuf.next,psBuf.size);

//	cout << (unsigned int)UserInfo::unpack<<endl;
	printf("func=%d",&UserInfo::unpack);
	return 0;
}

/*
 * g++ -c serialize/*.cpp
 * ar rs libserialize.a *.o
 * g++ test.cpp -L. -lserialize -Iserialize -o test*/
