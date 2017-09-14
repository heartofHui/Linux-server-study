#include <iostream>

#include <vector>
using namespace std;

std::vector<std::string> split(std::string str, std::string pattern)
{
	size_t pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


int main()
{
	string str = "name,age,time,address,,desc";
	vector<string> arr;
	arr = split(str, ",");
	vector<string>::iterator it = arr.begin();
	while (it != arr.end())
	{
		cout<<*it<<endl;
		it++;
	}
	return 0;
}
