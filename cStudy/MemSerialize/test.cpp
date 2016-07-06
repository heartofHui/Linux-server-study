#include <iostream>
#include <string>
#include <stdio.h>
#include "serialize.h"

using namespace std;
struct STRING
{
	int32_t len;
	char s[1024];
	STRING()
	{
		len = 0;
		memset(s,0,2014);
	}
};

struct UserInfo
{
private:
	int32_t age;
	int32_t height;
	STRING name;
public:
	UserInfo()
	{
		age = 1;
		height = 300;
		name.len = 2;
		strcpy((name.s),"ss");
	}
	bool pack(Buffer* buff)
	{
		MemSerialize(age, buff);
		MemSerialize(height, buff);
		MemSerialize(name.len, buff);
		MemSerialize(name.s, buff);
		return true;
	}
	bool unpack()
	{
		return true;
	}
};

int main()
{
	UserInfo uInfo;
	Buffer* buff = new Buffer();
	uInfo.pack(buff);
	//cout<<(buff->data)<<endl;

	for(int i=0;i<buff->next;i++)
	{
		printf("%X\n", buff->data[i]);
	}
	cout<<sizeof(int32_t)<<endl;
	cout<<buff->next<<endl;
	return 0;
}
