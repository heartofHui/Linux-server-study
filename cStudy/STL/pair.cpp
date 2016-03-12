/*************************************************************************
    > File Name: pair.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月27日 20:40:08
 ************************************************************************/
#include <iostream>
#include <string>
using namespace std;

int main()
{

	pair<char,int> p1;
	pair<string,int> p2;
	p1.first='c';
	p1.second=100;
	p2=make_pair("age",12);
	cout<<p1.first<<"=>"<<p1.second<<endl;
	cout<<p2.first<<"=>"<<p2.second<<endl;
	return 0;
}
