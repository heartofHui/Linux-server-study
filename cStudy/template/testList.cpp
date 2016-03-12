/*************************************************************************
    > File Name: testList.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年01月27日 11:54:16
 ************************************************************************/
#include <iostream>
#include "glist.h"
using namespace std;
int main()
{
	Glist<int> intList;
	Glist<char> charList;
	intList.insert(3);
	intList.insert(5);
	charList.insert('s');
	charList.insert('c');
	cout<<"int list len"<<intList.getLength()<<endl;
    cout<<"char list len:"<<charList.getLength()<<endl;
	return 0;
}
//定义一个类模板，在实例化的时候可以实例化任意类型的结构

//template <模板参数>