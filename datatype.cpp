/*************************************************************************
    > File Name: datatype.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月 3日 14:10:39
 ************************************************************************/
#include <iostream>
#include <typeinfo>
using namespace std;
int main()
{
	int a=10;
	cout<<typeid(a)==typeid(int)<<endl;
	return 0;
}
