/*************************************************************************
    > File Name: str.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月17日 17:45:53
 ************************************************************************/
#include <iostream>

#include <string>
#include <stdio.h>
using namespace std;
#define STR "ddd"
#define LIMIT 0.3
enum{
	AAA=10,
	BBB=20,
	CCC=21
};

int main()
{
	int a=10;
	int s=20;
	char res[128];
	snprintf(res,128,"%d%d\n",a,s);
	cout<<res<<endl;
	cout<<float(10)/float(6)<<endl;
	//string ss="asd"+string(10);
	//cout<<ss<<endl;
	cout<<LIMIT<<endl;
	cout<<STR<<endl;
//	int a=10;
	int * p=&a;
	cout<<*p<<endl;
	cout<<AAA<<endl;
	cout<<CCC<<endl;
	char ds[128]="话话\n";
	cout<<ds<<endl;
	return 0;
}
