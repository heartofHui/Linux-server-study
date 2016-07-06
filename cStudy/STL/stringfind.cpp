/*************************************************************************
    > File Name: stringfind.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年04月19日 23:37:53
 ************************************************************************/
#include <iostream>

#include <string>

using namespace std;

int main()
{

	string a1="love you";
	string a2="love";
	if(a1.find(a2)!=string::npos)
	{
		cout<<"contain"<<endl;
		cout<<a1.find(a2)<<endl;
		cout<<a1.substr(4)<<endl;
	}
	else
	{

		cout<<"no contain"<<endl;
	}
	return 0;

}
