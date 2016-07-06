/*************************************************************************
    > File Name: static.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年04月 7日 11:04:24
 ************************************************************************/
#include <iostream>

using namespace std;

int32_t getStatic()
{

	static int32_t i=10;
	--i;
	return i;
}

int main()
{

	while(true)
	{
		int32_t res=getStatic();
		if(res<=0)
		{
			break;
		}
		cout<<res<<endl;
	}
	return 0;
}
