#include <iostream>
#include <auto_ptr.h>

using namespace std;
class Obj
{
public:
	Obj();
	~Obj();
private:

};


int main()
{
	auto_ptr<int> i(10);

	return 0;
}
