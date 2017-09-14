#ifndef __BASE_DATA_STRUCT_DEF
#define __BASE_DATA_STRUCT_DEF
#include <stdio.h>
#include "serialize.h"

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned char BYTE;

using namespace std;

class PackHeader
{
private:
	int16 len; //pack length
	int32 type; //pack type
	int8 sharding_id;
	BYTE content[4096];
public:
	PackHeader()
	{
		len = 0;
		type = 0;
		sharding_id = 0;
		memset(content, 0, 4096);//content = "";
	}
	bool pack(Buffer* buffer)
	{

	}
};

struct STRING
{
	int32_t len;
	char s[1024];
	STRING()
	{
		len = 0;
		memset(s, 0, 2014);
	}
	bool pack(Buffer* buffer)
	{
		MemSerialize(len, buffer);
		MemSerialize(s, buffer);
		return true;
	}
	bool unpack(Buffer& buffer)
	{
		MemDeseriaize(len, buffer, sizeof(int32_t));
		MemDeseriaize(s, buffer, len);
		return true;
	}
	void dump()
	{
		cout << " s = " << s << endl;
	}
};

#endif
