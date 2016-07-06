#include <iostream>

class Point
{
private:
	int x;
	int y;
public:
	Point(int xVal, int yVal) :
			x(xVal), y(yVal)
	{
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
};

template<class MyObj>
class CountRef
{
public:
	int getCount()
	{
		return count;
	}
	int addCount()
	{
		++count;
	}
	int subCount()
	{
		--count;
	}
private:
	friend class SmartPtr;
	CountRef(MyObj* ptr) :
			ob(ptr), count(1)
	{
	}
	int count;
	MyObj* ob;
};

template<class MyObj>
class SmartPtr
{
private:
	CountRef* ref;
public:
	SmartPtr(MyObj* ptr) :
			ref(new CountRef(ptr))
	{
	}
	SmartPtr(const SmartPtr& sp) :
			ref(sp.ref)
	{
		++ref->count;
		//++ref->count;
	}
	SmartPtr& operator = (const SmartPtr& sp)
	{
		++sp.ref->count;
		ref = sp.ref;
		return *this;
	}

};
