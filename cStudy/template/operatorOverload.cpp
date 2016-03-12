
#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
    Date dt(2015,12,32);
    cout<<dt.getYear()<<" "<<dt.getMonth()<<" "<<dt.getDay()<<endl;
    Date dtother(2015,12,32);
    if(dt==dtother)
    {
        cout<<"equal"<<endl;
    }
    else
    {
        cout<<"no"<<endl;
    }
    return 0;
}
