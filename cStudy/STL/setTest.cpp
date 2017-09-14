#include <iostream>
#include <set>
#include <map>
using namespace std;


struct StruNpcCardInfo
{
	int miRoleId;
	int miOdds;
	int miQuality;
	StruNpcCardInfo()
	{
		miRoleId = 0;
		miOdds = 0;
		miQuality = 0;
	}
};

struct StruNpcCardInfoSort // 重载的比较函数，按照定义的比较规则，如果连个结构体的miOdds值一样，会被认为是一个对象不在插入set中。
{
public:
	bool operator ()(StruNpcCardInfo s1, StruNpcCardInfo s2) const
	{
		cout<<"s1="<<s1.miRoleId<<" s2="<<s2.miRoleId<<" return="<<(s1.miRoleId > s2.miRoleId)<<endl;
		//return s1.miOdds > s2.miOdds;
		if (s1.miOdds != s2.miOdds)
		{
			return s1.miOdds > s2.miOdds;
		}
		else
		{
			return s1.miRoleId > s2.miRoleId;
		}
	}
};

typedef map<int, set<StruNpcCardInfo,StruNpcCardInfoSort> > INTMAP2SET;

int main()
{
//	set<StruNpcCardInfo,StruNpcCardInfoSort> stest;
//	set<StruNpcCardInfo> set1,set2;
//	{
//		StruNpcCardInfo s1,s2,s3,s4,s5,s6;
//		s1.miOdds = 10;
//		s2.miOdds = 30;
//		s3.miOdds = 50;
//
//		s4.miOdds = 20;
//		s5.miOdds = 40;
//		s6.miOdds = 60;
//
//		set1.insert(s1);
//		set1.insert(s2);
//		set1.insert(s3);
//
//		set2.insert(s4);
//		set2.insert(s5);
//		set2.insert(s6);
//	}
//
//	set_union(set1.begin(),set1.end(),set2.begin(),set2.end(),inserter(stest, stest.end()));
////	StruNpcCardInfo s1,s2;
////	s1.miOdds=10;
////	s2.miOdds=20;
////	stest.insert(s1);
////	stest.insert(s2);
//	set<StruNpcCardInfo,StruNpcCardInfoSort>::iterator it = stest.begin();
//	for (; it != stest.end(); it++)
//	{
//		cout << " odds = " << it->miOdds << endl;
//	}
//
//
//	set<int> sint;
//	sint.insert(10);
//	sint.insert(11);
//	sint.insert(12);
//	for(set<int>::iterator it1 = sint.begin();it1!=sint.end();it1++)
//	{
//		cout<<" it "<< it<< endl;
//	}

	map<int, set<StruNpcCardInfo,StruNpcCardInfoSort> > testMapS;

	set<StruNpcCardInfo,StruNpcCardInfoSort> set1;
	for(int i=0;i<10;i++)
	{
		StruNpcCardInfo tmp;
		//tmp.miOdds = i;
		tmp.miRoleId = i;
		set1.insert(tmp);
		cout<<" i = "<<i<<endl;
	}
	cout<<"set size = "<<set1.size()<<endl;
	testMapS.insert(make_pair(1, set1));
	cout<<"size="<<testMapS[1].size()<<endl;

	return 0;
}
