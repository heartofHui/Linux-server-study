#ifndef __MEMORY_SERIALIZE
#define __MEMORY_SERIALIZE

#include <string>
#include <string.h>
#include <stdlib.h>

#define INI_BUFF_SIZE 128
#define MAX_BUFF_SIZE 2048

const int32_t _i = 1;

// TPC/IP协议网络字节序大多采用的是大端模式，因此本地数据在进行网络传输时需要转换为网络字节序
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
void MemSerialize(int32_t t, Buffer* b);
void MemSerialize(int64_t t, Buffer* b);
void MemSerialize(float t, Buffer* b);
void MemSerialize(double t, Buffer* b);

void MemSerialize(char* s, Buffer* b);

void MemDeseriaize(int32_t& t, Buffer& b, int32_t size);
void MemDeseriaize(int64_t& t, Buffer& b, int32_t size);
void MemDeseriaize(char* s, Buffer& b, int32_t size);

#endif
