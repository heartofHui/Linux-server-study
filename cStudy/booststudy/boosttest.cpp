#include <boost/regex.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string line;
	boost::regex pat("^Subject:(Re|Aw:)*(.*)");
	while (cin)
	{
		getline(cin, line);
		boost::smatch matches;
		if (boost::regex_match(line, matches, pat))
		{
			cout << matches[2] << endl;
		}
	}
	return 0;
}
//g++ boosttest.cpp -o test -lboost_regex
