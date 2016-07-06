/*************************************************************************
    > File Name: char.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月14日 19:51:59
 ************************************************************************/
#include <iostream>
using namespace std;
int main()
{

	char *c=NULL;

	c=new char[10];

	if(c==NULL)
		cout<<"null"<<endl;
	return 0;
}
