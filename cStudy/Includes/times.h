#ifndef TIMES_FUNCTION_DEF
#define TIMES_FUNCTION_DEF
#include <sys/time.h>


int64_t getTimeMsec() //获取毫秒
{
    struct  timeval    tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif
