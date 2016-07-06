/*************************************************************************
    > File Name: try-catch.c
    > Author: chenhui
    > Mail: ********* 
    > Created Time: 2016年03月14日 16:07:12
 ************************************************************************/
#include <iostream>
#include <exception>

using namespace std;

int main()
{
    try {
        int *arr = new int[10000000];
    }catch (exception& ex){
        cout<<"exception:"<<ex.what()<<endl;
    }
    return 0;
}
