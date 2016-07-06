#include <iostream>
#include <stdio.h>
using namespace std;
void set(int & i)
{
	i=101;
}

int main()
{
	int i=0;
	int b=i++;
	cout<<"b="<<b<<endl;
    cout<<"asd"<<endl;

	int s;
	set(s);
	cout<<s<<endl;
    
	int32_t in=1;
	int64_t a1=1073741824;
	in=(int32_t)a1*a1/10000000000;
	cout<<"in:"<<in<<endl;
	
	try{
		int *arr=new int[100000000000000];

	}catch(exception& e)
	{
		cout<<"Standard exception:"<<e.what()<<endl;
	}
	
	char str[32] = {0};
	strcpy(str,"chen");
	cout<<str<<endl;
	return 0;
}
