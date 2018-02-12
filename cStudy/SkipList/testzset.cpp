#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "../Includes/times.h"
#include "../Includes/rediszset.h"
using namespace std;

void test_insert(ClZset& zset)
{
	cout<<"--test insert--"<<endl;
	int32_t mem=1,score=0;
	cout<<"input mem&score:";
	cin>>mem>>score;
	while(mem != 0)
	{
		int64_t timeStart = getTimeUsec();
		zset.zAdd(mem, score);
		int64_t timeEnd = getTimeUsec();
		zset.printzsetlist();
		cout<<"input mem&score:";
		cin>>mem>>score;
	}
}

void test_delete(ClZset& zset)
{
	cout << "--test delete--,input delete member:";
	int32_t deleteKey = 0;
	cin >> deleteKey;
	int64_t timeStart = getTimeUsec();
	zset.zrem(deleteKey);
	int64_t timeEnd = getTimeUsec();
	printf("length:%d,use time:%dus\n", zset.zCount(), timeEnd - timeStart);
}

void test_delete_range(ClZset& zset)
{
	cout << "--test_delete_range--,input start,end,limit:";
	int64_t start, end, limit;
	cin >> start >> end >> limit;

	int64_t timeStart = getTimeUsec();
	zset.zRemRangeByRank(start, end, limit);
	int64_t timeEnd = getTimeUsec();
	printf("length:%d,use time:%dus\n", zset.zCount(), timeEnd - timeStart);
#ifdef CODE_TEST_LOG
	zset.printzsetlist();
#endif
}

void test_delete_range_byscore(ClZset& zset)
{
	cout << "--test_delete_range_byscore--,input start,end,limit:";
	int64_t start, end, limit;
	cin >> start >> end >> limit;

	int64_t timeStart = getTimeUsec();
	zset.zRemRangeByScore(start, end, limit);
	int64_t timeEnd = getTimeUsec();
	printf("length:%d,use time:%dus\n", zset.zCount(), timeEnd - timeStart);
#ifdef CODE_TEST_LOG
	zset.printzsetlist();
#endif
}

void test_zrange_byscore(ClZset& zset)
{
	cout << "--test_zrange_byscore--,input start,end,limit:";
	int64_t start, end, limit;
	cin >> start >> end >> limit;
	int64_t timeStart = getTimeUsec();
	std::vector<NodeValue> rangeRes;
	zset.zRangeByScore(start,end,rangeRes,true,limit);
	int64_t timeEnd = getTimeUsec();
	printf("size:%d,use time:%lldus\n", rangeRes.size(), timeEnd - timeStart);
	for(vector<NodeValue>::iterator it = rangeRes.begin();it!=rangeRes.end();it++)
	{
		printf("member:%llu,score:%llu\n",it->member,it->score);
	}
}

void speed_test_insert(ClZset& zset)
{
	cout << "--speed_test_insert--" << endl;
	int64_t end=1;
	cout << "input:" << endl;
	cin>>end;
	int64_t timeStart = getTimeMsec();
	for(int i=1;i<=end;i++)
	{
		zset.zAdd(i,i+5);
	}
	int64_t timeEnd = getTimeMsec();
	printf("length:%d,use time:%dms\n",zset.zCount(),timeEnd-timeStart);
}

void test_zrange(ClZset& zset)
{
	cout << "--speed_test_insert--,input start,end,limit:";
	int64_t start,end,limit;
	cin>>start>>end>>limit;

	std::vector<NodeValue> rangeRes;
	int vecUsetime=0;
	int64_t timeStart = getTimeUsec();
	zset.zRange(start,end,rangeRes,true,limit);
	int64_t timeEnd = getTimeUsec();
	printf("size:%d,use time:%lldus,vec use time:%dus\n", rangeRes.size(), timeEnd - timeStart,vecUsetime);
	for(vector<NodeValue>::iterator it = rangeRes.begin();it!=rangeRes.end();it++)
	{
		printf("mem:%llu,score:%llu\n",it->member,it->score);
	}
}

void test_zrank(ClZset& zset)
{
	int64_t member;
	cout << "input:";
	cin>>member;
	int64_t rank=0;
	int64_t timeStart = getTimeUsec();
	rank = zset.zRank(member);
	int64_t timeEnd = getTimeUsec();
	printf("length:%d,use time:%dus,rank:%lld\n",zset.zCount(),timeEnd-timeStart,rank);
}

void test_destroy(ClZset& zset)
{
	int64_t timeStart = getTimeMsec();
	zset.destroy();
	int64_t timeEnd = getTimeMsec();
	printf("%s,length:%d,use time:%dms\n",__FUNCTION__, zset.zCount(),timeEnd-timeStart);
}

void test_zscore(ClZset& zset)
{
	int64_t member,score;
	cin>>member;
	int64_t timeStart = getTimeUsec();
	bool exists = zset.zScore(member, score);
	int64_t timeEnd = getTimeUsec();
	if(exists)
	{
		printf("%s,length:%d,use time:%dus,score:%lld\n",__FUNCTION__, zset.zCount(),timeEnd-timeStart,score);
	}
	else
	{
		printf("%s,length:%d,use time:%dus,not found\n",__FUNCTION__, zset.zCount(),timeEnd-timeStart);
	}
}

int main()
{
	ClZset zset;
	int64_t begin,end;
	string input;
	cout<<"please input:"<<endl;
	cin>>input;
	while(input!="quit")
	{
		if(input=="insert")
		{
			test_insert(zset);
		}
		else if(input=="zremrangebyrank")
		{
			test_delete_range(zset);
		}
		else if(input=="zremrangebyscore")
		{
			test_delete_range_byscore(zset);
		}
		else if(input=="zrangebyscore")
		{
			test_zrange_byscore(zset);
		}
		else if(input=="speedinsert")
		{
			speed_test_insert(zset);
		}
		else if(input=="zRank")
		{
			test_zrank(zset);
		}
		else if(input=="test_zrange")
		{
			test_zrange(zset);
		}
		else if(input == "destroy")
		{
			test_destroy(zset);
		}
		else if(input == "test_delete")
		{
			test_delete(zset);
		}
		else if(input == "test_zscore")
		{
			test_zscore(zset);
		}
		cout<<"please input:"<<endl;
		cin>>input;
	}
	//zset.printzsetlist();
	return 0;
}
