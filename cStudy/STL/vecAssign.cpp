/*************************************************************************
    > File Name: vecAssign.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年02月27日 19:43:36
 ************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

#include <iterator>
using namespace std;
int main()
{
	int ary[]={1,2,3,4};
	vector<int> v;
	v.assign(ary,ary+sizeof(ary)/sizeof(int));
	int i=0;
	for(;i<v.size();i++)
	{
		cout<<v[i]<<endl;
	}
	return 0;
}
