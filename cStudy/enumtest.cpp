/*************************************************************************
    > File Name: enumtest.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年04月21日 21:49:21
 ************************************************************************/
#include <iostream>

using namespace std;

int main()
{

	enum{
		aa = 1,
		bb=2
	};
	int i = aa;
	cout<<i<<endl;
	int j=1;

	if(j==aa)
	{
		cout<<"yes"<<endl;
	}
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<2;j++)
		{
			cout<<"asd"<<endl;
		}
		cout<<"-----"<<endl;
	}

	return 0;
}
