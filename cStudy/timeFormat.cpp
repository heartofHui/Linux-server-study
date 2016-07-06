#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int32_t getTimeToDay()
{
    time_t rawtime;
    struct tm* timeInfo;
    char timeE[128]={0};
    time(&rawtime);
    timeInfo=localtime(&rawtime);
    strftime(timeE,sizeof(timeE)-1,"%Y%m%d",timeInfo);
    return atoi(timeE);
}

int main()
{

    int32_t day=getTimeToDay();
    cout<<day<<endl;
    return 0;
}