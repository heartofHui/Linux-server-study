/*************************************************************************
    > File Name: vecback.cpp
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016骞�2鏈�7鏃�21:48:49
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

template<class T,class D>
class Member
{
    public:
        Member(T t,D d):name(t),sal(d){};
        void Print()
        {
            cout<<"name:"<<name<<" sal:"<<sal<<endl;
        }
    private:
        T name;
        D sal;
};

//template<class T,class D>
//void Member::Print()
//{
//    cout<<"name:"<<name<<" sal:"<<sal<<endl;
//}
int main()
{
    typedef Member<string,int> M;//typedef
    vector<M> v;
    v.push_back(M("banana",100));
    v.push_back(M("apple",200));
    v.push_back(M("cherry",300));

    vector<M>::iterator it;
    for(it=v.begin();it!=v.end();it++)
    {
        (*it).Print();
    }
    return 0;
}
