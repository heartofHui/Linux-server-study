#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <pthread.h>

using namespace std;
pthread_mutex_t count_mutex=PTHREAD_MUTEX_INITIALIZER;

template<class T>
struct STRU_CACHE_ITEM
{
public:
    int32_t _expireTime;
    T _item;
public:
    STRU_CACHE_ITEM(void) : _expireTime(0)
    {
        return;
    }
};

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL = 300>
class CacheTemPlate
{
private:
    std::map< KEY_TYPE, STRU_CACHE_ITEM<VAL_TYPE> > _cacheMap;

public:

    CacheTemPlate(void);

    ~CacheTemPlate(void);

    void addCache(const KEY_TYPE& key, const VAL_TYPE& val, int32_t timeNow, int32_t ttl = DEFAULT_TTL);

    bool getCache(const KEY_TYPE& key, int32_t timeNow, VAL_TYPE& val);

    void clearCache(const KEY_TYPE& key);

    int32_t getTtl(void) const;
};

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL>
CacheTemPlate<KEY_TYPE, VAL_TYPE, DEFAULT_TTL>::CacheTemPlate(void)
{
	pthread_mutex_lock(&count_mutex);//线程锁
    _cacheMap.clear();
    pthread_mutex_unlock(&count_mutex);
    return;
}

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL>
CacheTemPlate<KEY_TYPE, VAL_TYPE, DEFAULT_TTL>::~CacheTemPlate(void)
{
	pthread_mutex_lock(&count_mutex);//线程锁
    _cacheMap.clear();
    pthread_mutex_unlock(&count_mutex);
    return;
}

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL>
void CacheTemPlate<KEY_TYPE, VAL_TYPE, DEFAULT_TTL>::addCache(const KEY_TYPE& key, const VAL_TYPE& val, int32_t timeNow, int32_t ttl)
{
	pthread_mutex_lock(&count_mutex);//线程锁
    std::pair<typename std::map<KEY_TYPE, STRU_CACHE_ITEM<VAL_TYPE> >::iterator, bool> pr;
    pr = _cacheMap.insert(typename std::map<KEY_TYPE, STRU_CACHE_ITEM<VAL_TYPE> >::value_type(key, STRU_CACHE_ITEM<VAL_TYPE>()));
    STRU_CACHE_ITEM<VAL_TYPE>& cache = pr.first->second;
    cache._item = val;
    cache._expireTime = timeNow + ttl;
    pthread_mutex_unlock(&count_mutex);
    return;
}

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL>
bool CacheTemPlate<KEY_TYPE, VAL_TYPE, DEFAULT_TTL>::getCache(const KEY_TYPE &key, int32_t timeNow, VAL_TYPE &val)
{
	pthread_mutex_lock(&count_mutex);//线程锁
    typename std::map<KEY_TYPE, STRU_CACHE_ITEM<VAL_TYPE> >::const_iterator iter = _cacheMap.find(key);
    if (iter == _cacheMap.end())
    {

        return false;
    }
    const STRU_CACHE_ITEM<VAL_TYPE>& cache = iter->second;
    if (cache._expireTime < timeNow)
    {

        _cacheMap.erase(key);
        return false;
    }
    val = cache._item;
    pthread_mutex_unlock(&count_mutex);
    return true;
}

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL>
void CacheTemPlate<KEY_TYPE, VAL_TYPE, DEFAULT_TTL>::clearCache(const KEY_TYPE &key)
{
	pthread_mutex_lock(&count_mutex);//线程锁
    _cacheMap.erase(key);
    pthread_mutex_unlock(&count_mutex);
    return;
}

template<class KEY_TYPE, class VAL_TYPE, int32_t DEFAULT_TTL>
int32_t CacheTemPlate<KEY_TYPE, VAL_TYPE, DEFAULT_TTL>::getTtl(void) const
{
    return DEFAULT_TTL;
}

typedef int USERID;
struct Info{
	int age;
	string name;
};

void PrintUInfo(struct Info info)
{
	cout<<"age:"<<info.age<<",name:"<<info.name<<endl;
}

int main()
{
	time_t timeNow=time(NULL);
	CacheTemPlate<USERID,Info,20> userInfoCache;
	USERID userId=10001;
	Info uInfo;
	uInfo.age=20;
	uInfo.name="chenhui";
	userInfoCache.addCache(userId,uInfo,timeNow);

	Info newInfo;
	userInfoCache.getCache(userId,timeNow,newInfo);

	PrintUInfo(newInfo);

	return 0;
}



