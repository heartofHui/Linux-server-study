/*************************************************************************
    > File Name: tes.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月24日 16:26:12
 ************************************************************************/
#include <iostream>
using namespace std;

void set(bool * a)
{
	*a=true;
}
int main()
{
	bool i;
	set(&i);
	cout<<i<<endl;
	return 0;

}
