/*************************************************************************
    > File Name: glist.h
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年01月27日 11:12:12
 ************************************************************************/
const int MAX_LEN=100;
template<class ItemType>

class Glist
{
	private:
		int length;
		int currentpos;
		ItemType list[MAX_LEN];
	public:
		Glist()
		{
			length=0;
			currentpos=0;
		}
		void insert(const ItemType & item)
		{
		    if(length>=MAX_LEN)
		    {
		        return;
		    }
			list[++length]=item;
		}
		int getLength()
		{
			return length;
		}
		bool isEmpty()
		{
		    return (length==0);
		}
		bool isFull()
		{
		    return (length==MAX_LEN);
		}
		void deleteItem(const ItemType & item)
		{
		    int index=0;
		    while(index<length && list[index]!=item)
		    {
		        index++;
		    }
		    if(index<length)
		    {
		        list[index]=list[length-1];
		    }
		    length--;
		}
		int indexOf(const ItemType & item)
		{
		    int index=0;
		    while(index<length && list[index]!=item)
		    {
		        index++;
		    }
		    return (index<length)?index:-1;
		}
		ItemType getValueByIndex(int index)
		{
		    return list[index];
		}
};
