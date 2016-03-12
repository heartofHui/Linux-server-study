#include <iostream>
#include <string>
using namespace std;
template <typename Sample>//模板函数，比函数重载要方便！
void output(Sample val)
{
    cout<<"val:"<<val<<endl;
}

int main()
{
    output("sss");
    output(12.3);
    return 0;
}


