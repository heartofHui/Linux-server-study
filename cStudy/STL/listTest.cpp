#include <iostream>
#include <list>

using namespace std;
int main()
{
	int32_t protocol = 0;
	cin>>protocol;
	std::list<int32_t> listTest;
	listTest.push_back(60);
	listTest.push_back(70);
	listTest.push_back(80);
	listTest.push_back(90);
	int32_t upgradeProtocol = 0;
	for (std::list<int32_t>::iterator itList = listTest.begin();;)
	{
		int32_t itNow = *itList;
		int32_t itNext = 0;
		itList++;
		if(itList != listTest.end())
		{
			itNext = *itList;
			cout<<"itNow="<<itNow<<",itNext="<<itNext<<endl;
			if(protocol >= itNow && protocol < itNext)
			{
				upgradeProtocol = itNow;
				break;
			}
		}
		else
		{
			upgradeProtocol = itNow;
			break;
		}
	}
	cout<<"upgradeProtocol="<<upgradeProtocol<<endl;
	return 0;
}
