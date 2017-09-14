#ifndef __USERINFO_STRUCT_DEF
#define __USERINFO_STRUCT_DEF
#include "BaseStruct.h"
#include "serialize.h"

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
		age = 0;
		height = 0;
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
		cout << "unpack start" << endl;
		printf("this=%d\n", this);

		MemDeseriaize(age, buff, sizeof(int32_t));
		MemDeseriaize(height, buff, sizeof(int32_t));
		name.unpack(buff);
		return true;
	}
	void dump()
	{
		cout << " age =" << age << endl;
		cout << " height =" << height << endl;
		name.dump();
	}
};
#endif
