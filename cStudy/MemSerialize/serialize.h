#ifndef __MEMORY_SERIALIZE
#define __MEMORY_SERIALIZE

#include <string>
#include <string.h>
#include <stdlib.h>

#define INI_BUFF_SIZE 128
#define MAX_BUFF_SIZE 2048

const int32_t _i = 1;

#define isBigEndian() ((*(char*)& _i)==0)

struct Buffer
{
	char * data;
	int next;
	size_t size;
public:
	Buffer()
	{
		data = (char *)malloc(INI_BUFF_SIZE);
		memset(data,0,INI_BUFF_SIZE);
		size = INI_BUFF_SIZE;
		next = 0;
	}
};



//struct Buffer * new_buffer()
//{
//	struct Buffer* b = malloc(sizeof(Buffer));
//	b->data = malloc(INI_BUFF_SIZE);
//	b->size = INI_BUFF_SIZE;
//	b->next = 0;
//	return b;
//}

void beNetData(int32_t& t);
void beNetData(int64_t& t);
void beNetData(float & t);
void beNetData(double& t);
bool reserve_space(Buffer* b, size_t bytes);
void MemSerialize(int32_t t,Buffer* b);
void MemSerialize(int64_t t,Buffer* b);
void MemSerialize(std::string s,Buffer* b);
void MemSerialize(char* s,Buffer* b);

#endif
