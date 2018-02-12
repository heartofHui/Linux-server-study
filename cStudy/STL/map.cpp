/*************************************************************************
    > File Name: map.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2017年12月21日 17:23:34
 ************************************************************************/
#include <iostream>
#include <stdio.h>
#include <map>
#include "../Includes/times.h"
#ifdef __GNUC__
#include <ext/hash_map>
#else
#include <hash_map>
#endif

namespace std
{
using namespace __gnu_cxx;
}

using namespace std;

typedef hash_map<int,int> HASHMAPINT2INT;
typedef map<int,int> MAPINT2INT;

int main()
{

	MAPINT2INT mapTest;
	int64_t timeBegin = getTimeMsec();
	for(int i=0;i<5000000;i++)
	{
		mapTest[i]=i;
	}
	int64_t timeEnd = getTimeMsec();
	printf("map use time:%d\n",timeEnd-timeBegin);

	HASHMAPINT2INT hamp;
	timeBegin = getTimeMsec();
	for(int i=0;i<5000000;i++)
	{
		hamp[i]=i;
	}
	timeEnd = getTimeMsec();
	printf("hashmap use time:%d\n",timeEnd-timeBegin);
	return 0;
}
