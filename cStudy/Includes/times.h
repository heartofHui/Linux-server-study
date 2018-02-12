#ifndef TIMES_FUNCTION_DEF
#define TIMES_FUNCTION_DEF
#include <sys/time.h>
typedef long long int64;
typedef unsigned long long uint64;
/*function:获取当前时间，精确到毫秒
 * */
int64_t getTimeMsec()
{
    struct  timeval    tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/*function:获取当前时间，精确到微秒
 * */
int64_t getTimeUsec()
{
    struct  timeval    tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

/*function:返回天开始时间戳
 *args
 * 		time:当前时间戳
 */
int32_t getDayBeginTime(const int32_t time)
{
	time_t t = time;
	struct tm zeroTm;
	localtime_r(&t, &zeroTm);//
	zeroTm.tm_hour = 0;
	zeroTm.tm_min = 0;
	zeroTm.tm_sec = 0;
	int32_t timeZero = mktime(&zeroTm);
	return timeZero;
}

#endif
