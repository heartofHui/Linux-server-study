#include <iostream>
#include <fstream> //
#include <vector>
#include "../Includes/times.h"
using namespace std;

const int BUILDING_SIZE = 10;//

template <typename itemtype>
void Print(vector<itemtype> vec)//泛型函数
{
    int size=vec.size();
    for(int i=0;i<size;i++)
    {
        cout<<vec[i]<<endl;//按下表访问元素
    }
}

int main()
{
	vector<int> v1;//创建一个空的vector对象

	vector<int> v2(10,1);//创建一个包含10个int类型数据的vector，并且都初始化为1
	int64_t timeStart = getTimeUsec();
	for (int i = 1; i < 100; i++)
	{
		v1.push_back(i);
	}
	int64_t timeEnd = getTimeUsec();
	cout<<"timeuse:"<<timeEnd - timeStart <<endl;
//	cout<<"v1 first:"<<v1.front()<<endl;
//	cout<<"v1 back:"<<v1.back()<<endl;
//	cout<<"v1 capacity:"<<v1.capacity()<<endl;
//	cout<<"v1 size:"<<v1.size()<<endl;
//
//    cout<<"v2 first:"<<v2.front()<<endl;
//	cout<<"v2 back:"<<v2.back()<<endl;
//	cout<<"v2 capacity:"<<v2.capacity()<<endl;
//	cout<<"v2 size:"<<v2.size()<<endl;
//
//    Print(v1);
//    int a=2;
//    v1.insert(2,1);
	return 0;
}




/*
c.assign(beg,end)c.assign(n,elem)
　　将[beg; end)区间中的数据赋值给c。将n个elem的拷贝赋值给c。
c.at(idx)
　　传回索引idx所指的数据，如果idx越界，抛出out_of_range。


c.back()      // 传回最后一个数据，不检查这个数据是否存在。
c.begin()     // 传回迭代器中的第一个数据地址。
c.capacity()  // 返回容器中数据个数。
c.clear()     // 移除容器中所有数据。
c.empty()     // 判断容器是否为空。
c.end()       // 指向迭代器中末端元素的下一个，指向一个不存在元素。
c.erase(pos)  // 删除pos位置的数据，传回下一个数据的位置。
c.erase(beg,end)  //删除[beg,end)区间的数据，传回下一个数据的位置。
c.front()     // 传回第一个数据。


get_allocator // 使用构造函数返回一个拷贝。


c.insert(pos,elem)    // 在pos位置插入一个elem拷贝，传回新数据位置。
c.insert(pos,n,elem)  // 在pos位置插入n个elem数据。无返回值。
c.insert(pos,beg,end) // 在pos位置插入在[beg,end)区间的数据。无返回值。

c.max_size()       // 返回容器中最大数据的数量。
c.pop_back()       // 删除最后一个数据。
c.push_back(elem)  // 在尾部加入一个数据。
c.rbegin()         // 传回一个逆向队列的第一个数据。
c.rend()           // 传回一个逆向队列的最后一个数据的下一个位置。
c.resize(num)      // 重新指定队列的长度。
c.reserve()        // 保留适当的容量。
c.size()           // 返回容器中实际数据的个数。
c1.swap(c2)
swap(c1,c2)        // 将c1和c2元素互换。同上操作。

operator[]         // 返回容器中指定位置的一个引用。
http://blog.chinaunix.net/uid-26000296-id-3785610.html
*/
