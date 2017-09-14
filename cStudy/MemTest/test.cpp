#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <memory>
#include <stdio.h>

using namespace std;

#define INI_BUFF_SIZE 128
#define MAX_BUFF_SIZE 2048

const int32_t _i = 1;

// TPC/IP协议网络字节序采用的大端模式，因此本地数据在进行网络传输时需要转换为网络字节序
#define isBigEndian() ((*(char*)& _i)==0)

class Buffer
{
public:
	unsigned char* data;
	int32_t next;
	size_t size;
	Buffer();
	~Buffer();
	Buffer(unsigned char * src, int32_t s);
	Buffer(Buffer& other);

};

void beNetData(int32_t& t);
void beNetData(int64_t& t);
void beNetData(float & t);
void beNetData(double& t);
bool reserve_space(Buffer* b, size_t bytes);
void MemSerialize(int32_t t,Buffer* b);
void MemSerialize(int64_t t,Buffer* b);
void MemSerialize(char* s,Buffer* b);

void MemDeseriaize(int32_t& t, Buffer& b, int32_t size);
void MemDeseriaize(int64_t& t,Buffer& b, int32_t size);
void MemDeseriaize(char* s,Buffer& b, int32_t size);


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
	//this->data = other.data;
	memcpy(this->data, other.data, other.size);
	//strlen(other.data);
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
	//printf("len:%d\n",strlen(s));
}

void MemDeseriaize(int32_t& t, Buffer& b, int32_t size)
{
	try{
		memcpy(&t, b.data + b.next, size);
		beNetData(t);
	} catch (...) {
		printf("catch exception\n");
	}
}

void MemDeseriaize(int64_t& t, Buffer& b, int32_t size)
{
	try{
		memcpy(&t, b.data + b.next, sizeof(size));
		beNetData(t);
	}catch(...)
	{
		printf("catch exception\n");
	}
}

void MemDeseriaize(char* s, Buffer& b, int32_t size)
{
	try{
		memcpy(s, b.data + b.next, sizeof(size));
	}catch(...)
	{
		printf("catch exception\n");
	}
}



void printBufferHex(unsigned char * buff, int32_t size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%02X", buff[i]);
	}
	printf("\n");
}

struct STRING
{
	int32_t len;
	char s[1024];
	STRING()
	{
		len = 0;
		memset(s,0,2014);
	}
	bool pack(Buffer* buffer)
	{
		MemSerialize(len, buffer);
		MemSerialize(s, buffer);
	}
	bool unpack(Buffer& buffer)
	{
		MemDeseriaize(len, buffer, sizeof(int32_t));
		buffer.next += sizeof(int32_t);
		MemDeseriaize(s, buffer, len);
		buffer.next += len;
	}
	bool dump()
	{
		cout<<" s = "<< s << endl;
	}
};


class UserInfo
{
public:
	int32_t age;
	int32_t height;
	STRING name;
public:
	UserInfo()
	{
		printf("construct UserInfo\n");
		age = 1;
		height = 300;
		name.len = 2;
		strcpy((name.s),"ss");
	}

	bool pack(Buffer* buff)
	{
		MemSerialize(age, buff);
		MemSerialize(height, buff);
		name.pack(buff);
		return true;
	}

	bool unpack(Buffer& buff)
	{
		cout<<"unpack start"<<endl;
		printf("this=%d",this);
		cout<<buff.size<<endl;
		cout<<buff.next<<endl;
		//printBufferHex(buff->data, buff->size);

//		MemDeseriaize(age, buff, sizeof(int32_t));
//		buff.next += sizeof(int32_t);
//		cout<<"unpack 1"<<endl;
//		MemDeseriaize(height, buff, sizeof(int32_t));
//		buff.next += sizeof(int32_t);
//		cout<<"unpack 2"<<endl;
//		name.unpack(buff);
//		cout<<"unpack end"<<endl;
		return true;
	}
	bool dump()
	{
		cout<<" age =" << age <<endl;
		cout<<" height =" << height <<endl;
		name.dump();
	}
};

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

	cout << buff->next << endl;

	unsigned char buf[1024] = { 0 }; // = buff->data;
	memcpy(buf, buff->data, buff->next);

	//printBufferHex(buf, buff->next);

	int32_t size = buff->next;

	Buffer psBuf(buf, size);

	//printBufferHex(psBuf.data, psBuf.size);

	printfBuffer(&psBuf);
	printf("-----------\n");

	UserInfo *recvUser = new UserInfo;
	recvUser->unpack(psBuf);
	recvUser->dump();
	printf("%d,%d\n",psBuf.next,psBuf.size);

	UserInfo recvUser1; //= new UserInfo;
	recvUser1.unpack(psBuf);
	//recvUser1->dump();
	printf("%d,%d\n",psBuf.next,psBuf.size);
//	cout << (unsigned int)UserInfo::unpack<<endl;
	printf("func=%d",&UserInfo::unpack);
	return 0;
}

/*
 * g++ -c serialize/*.cpp
 * ar rs libserialize.a *.o
 * g++ test.cpp -L. -lserialize -Iserialize -o test*/
