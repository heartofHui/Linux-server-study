// $_FILEHEADER_BEGIN ***************************
// 版权声明: 北京畅聊天下科技公司版权所有
//					Copyright (C) 2013-  Beijing ChangLiaoTianXia Tech Ltd.,co All Rights Reserved
// 文件名称: DataType.h
// 创建日期: 20130619 18:28
// 创 建 人: 周斌
// 文件说明: 基本结构
//
// 0.01 周斌 20130619 18:28
// 原因:
// $_FILEHEADER_END *****************************
#ifndef __DATATYPE_H_
#define __DATATYPE_H_
typedef long long            __int64;
typedef __int64				int64;
typedef unsigned char		uint8;
typedef signed int			int32;
typedef signed short		int16;

typedef int32				DataType_INT;

typedef int64				DataType_INT64;

typedef double	            DataType_DOUBLE;

typedef void*				DataType_POINTER;

typedef const void* 		DataType_CONSTPTR;

struct DataType_UNION;

struct DataType_STRING
{
    char* mpContent;
	int16  miLength;
};

struct DataType_STRREF
{
    const char* mpContent;
	int16  miLength;
};

struct DataType_VECTOR
{
    uint8* mpContent;
    int16  miLength;
};

struct DataType_CONDITION_VALUE
{
    int32 miFirst;
    int32 miSecond;
};

struct DataType_DATAVEC
{
    struct DataType_UNION* mpContent;
    int16  miLength;
};

enum{
    ENU_DATATYPE_INT = 0,
    ENU_DATATYPE_INT64,
    ENU_DATATYPE_DOUBLE,
    ENU_DATATYPE_PTR,
    ENU_DATATYPE_PTR_CONST,
    ENU_DATATYPE_STR,
    ENU_DATATYPE_STRREF,
    ENU_DATATYPE_VECTOR,
    ENU_DATATYPE_COND_VAL,
    ENU_DATATYPE_DATA_VEC,
    ENU_DATATYPE_REDIS_STATUS,
    ENU_DATATYPE_REDIS_ERROR,
    ENU_DATATYPE_REDIS_NULL,
    ENU_DATATYPE_INVALID
};

struct DataType_UNION
{
    uint8 miDataType;

    union{
        DataType_INT miIntValue;

        DataType_INT64 miIntValue64;

        DataType_DOUBLE mdbDoubleValue;

        DataType_POINTER mpPtr;

        DataType_CONSTPTR mpPtrConst;

        struct DataType_STRING  moString;

        struct  DataType_STRREF  moStrRefrence;

        struct DataType_VECTOR moVector;

        struct DataType_CONDITION_VALUE moConditionVal;

        struct DataType_DATAVEC moDataVec;
    } moData;

public:
    DataType_UNION()
    {
        miDataType = ENU_DATATYPE_INVALID;
        moData.moString.mpContent = NULL;
        moData.moString.miLength = 0;
    }
    void clear(void)
    {
        if (miDataType == ENU_DATATYPE_STR ||
            miDataType == ENU_DATATYPE_REDIS_STATUS ||
            miDataType == ENU_DATATYPE_REDIS_ERROR)
        {
            SAFE_DELETE(moData.moString.mpContent);
			moData.moString.miLength = 0;
        }
        else if (miDataType == ENU_DATATYPE_VECTOR)
        {
			SAFE_DELETE(moData.moVector.mpContent);
			moData.moVector.miLength = 0;
        }
        else if (miDataType == ENU_DATATYPE_DATA_VEC)
        {
            if (moData.moDataVec.mpContent != NULL)
            {
                delete[] moData.moDataVec.mpContent;
                moData.moDataVec.mpContent = NULL;
            }
			moData.moDataVec.miLength = 0;
        }
        miDataType = ENU_DATATYPE_INVALID;
    }
    ~DataType_UNION()
    {
        clear();
    }

    DataType_UNION& operator = (const DataType_UNION& aoObj)
    {
        if (&aoObj == this)
        {
            return *this;
        }
        clear();
        miDataType = aoObj.miDataType;

        switch(miDataType)
        {
        case ENU_DATATYPE_STR:
        case ENU_DATATYPE_REDIS_STATUS:
        case ENU_DATATYPE_REDIS_ERROR:
            moData.moString.miLength = aoObj.moData.moString.miLength;
            if (moData.moString.miLength > 0)
            {
                moData.moString.mpContent = new char[moData.moString.miLength + 1];
                if (moData.moString.mpContent == NULL)
                {
                    throw;
                }
                memset(moData.moString.mpContent, 0, moData.moString.miLength + 1);
                memcpy(moData.moString.mpContent, aoObj.moData.moString.mpContent, moData.moString.miLength);
            }
            break;
        case ENU_DATATYPE_VECTOR:
            moData.moVector.miLength = aoObj.moData.moVector.miLength;
            if (moData.moVector.miLength > 0)
            {
                moData.moVector.mpContent = new uint8_t[moData.moVector.miLength];
                if (moData.moVector.mpContent == NULL)
                {
                    throw;
                }
                memcpy(moData.moVector.mpContent, aoObj.moData.moVector.mpContent, moData.moVector.miLength);
            }
            break;
        case ENU_DATATYPE_STRREF:
            moData.moStrRefrence.miLength = aoObj.moData.moStrRefrence.miLength;
            moData.moStrRefrence.mpContent = aoObj.moData.moStrRefrence.mpContent;
            break;
        case ENU_DATATYPE_INT:
            moData.miIntValue = aoObj.moData.miIntValue;
            break;
        case ENU_DATATYPE_INT64:
            moData.miIntValue64 = aoObj.moData.miIntValue64;
            break;
        case ENU_DATATYPE_DOUBLE:
            moData.mdbDoubleValue = aoObj.moData.mdbDoubleValue;
            break;
        case ENU_DATATYPE_COND_VAL:
            moData.moConditionVal.miFirst = aoObj.moData.moConditionVal.miFirst;
            moData.moConditionVal.miSecond = aoObj.moData.moConditionVal.miSecond;
            break;
        case ENU_DATATYPE_PTR:
            moData.mpPtr = aoObj.moData.mpPtr;
            break;
        case ENU_DATATYPE_PTR_CONST:
            moData.mpPtrConst = aoObj.moData.mpPtrConst;
            break;
        case ENU_DATATYPE_DATA_VEC:
            moData.moDataVec.miLength = aoObj.moData.moDataVec.miLength;
            if (moData.moDataVec.miLength > 0)
            {
                moData.moDataVec.mpContent = new DataType_UNION[moData.moDataVec.miLength];
                if (moData.moDataVec.mpContent == NULL)
                {
                    throw;
                }
                for (int i = 0; i < moData.moDataVec.miLength; i++)
                {
                    moData.moDataVec.mpContent[i] = aoObj.moData.moDataVec.mpContent[i];
                }
            }
            break;
        case ENU_DATATYPE_REDIS_NULL:
            memset(&moData, 0, sizeof(moData));
            break;
        default:
            break;
        }
        return *this;
    }

    template<class T>
	DataType_UNION(const T& aoObj)
	{
        miDataType = ENU_DATATYPE_INVALID;
        moData.moString.mpContent = NULL;
        moData.moString.miLength = 0;
		operator = (aoObj);
	}

    template<class T>
	DataType_UNION(const T* apObj)
	{
        miDataType = ENU_DATATYPE_INVALID;
        moData.moString.mpContent = NULL;
        moData.moString.miLength = 0;
		operator = (apObj);
	}

#ifdef __APPLE__
    template<class T>
    DataType_UNION& operator = (const T value)
    {
        assert(false);
    }
#endif

    DataType_UNION& operator = (const int8_t aiIntValue)
    {
        clear();
        miDataType = ENU_DATATYPE_INT;
        moData.miIntValue = aiIntValue;
        return *this;
    }

    DataType_UNION& operator = (const uint8_t aiIntValue)
    {
        clear();
        miDataType = ENU_DATATYPE_INT;
        moData.miIntValue = aiIntValue;
        return *this;
    }

    DataType_UNION& operator = (const int16_t aiIntValue)
    {
        clear();
        miDataType = ENU_DATATYPE_INT;
        moData.miIntValue = aiIntValue;
        return *this;
    }

    DataType_UNION& operator = (const uint16_t aiIntValue)
    {
        clear();
        miDataType = ENU_DATATYPE_INT;
        moData.miIntValue = aiIntValue;
        return *this;
    }

#ifndef __APPLE__
    DataType_UNION& operator = (const DataType_INT64 aiIntValue64)
    {
        clear();
        miDataType = ENU_DATATYPE_INT64;
        moData.miIntValue64 = aiIntValue64;
        return *this;
    }

    DataType_UNION& operator = (const DataType_INT64 aiIntValue64)
    {
        clear();
        miDataType = ENU_DATATYPE_INT64;
        moData.miIntValue64 = aiIntValue64;
        return *this;
    }
#endif

    DataType_UNION& operator = (const int32_t aiIntValue)
    {
        clear();
        miDataType = ENU_DATATYPE_INT;
        moData.miIntValue = aiIntValue;
        return *this;
    }

    DataType_UNION& operator = (const uint32_t aiIntValue)
    {
        clear();
        miDataType = ENU_DATATYPE_INT64;
        moData.miIntValue64 = aiIntValue;
        return *this;
    }

    DataType_UNION& operator = (const int64_t aiIntValue64)
    {
        clear();
        miDataType = ENU_DATATYPE_INT64;
        moData.miIntValue64 = aiIntValue64;
        return *this;
    }

    DataType_UNION& operator = (const uint64_t aiIntValue64)
    {
        clear();
        miDataType = ENU_DATATYPE_INT64;
        moData.miIntValue64 = aiIntValue64;
        return *this;
    }

    DataType_UNION& operator = (const double adbDoubleValue)
    {
        clear();
        miDataType = ENU_DATATYPE_DOUBLE;
        moData.mdbDoubleValue = adbDoubleValue;
        return *this;
    }

    DataType_UNION& operator = (const char* apString)
    {
        switch(miDataType)
        {
            case ENU_DATATYPE_STR:
            case ENU_DATATYPE_REDIS_STATUS:
            case ENU_DATATYPE_REDIS_ERROR:
                if (moData.moString.mpContent == apString)
                {
                    return *this;
                }
                break;
            case ENU_DATATYPE_VECTOR:
                if (moData.moVector.mpContent == (void*)apString)
                {
                    return *this;
                }
                break;
            case ENU_DATATYPE_DATA_VEC:
                if (moData.moDataVec.mpContent == (void*)apString)
                {
                    return *this;
                }
                break;
            default:
                break;
        }
        clear();
        if (apString != NULL)
        {
            moData.moString.miLength = strlen(apString);
            if (moData.moString.miLength > 0)
            {
                miDataType = ENU_DATATYPE_STR;
                moData.moString.mpContent = new char[moData.moString.miLength + 1];
                if (moData.moString.mpContent == NULL)
                {
                    throw;
                }
                memset(moData.moString.mpContent, 0, moData.moString.miLength + 1);
                memcpy(moData.moString.mpContent, apString, moData.moString.miLength);
            }
        }
        return *this;
    }

    DataType_UNION& operator = (const std::string& aoString)
    {
        clear();
        moData.moString.miLength = strnlen(aoString.c_str(), aoString.size());
        if (moData.moString.miLength > 0)
        {
            miDataType = ENU_DATATYPE_STR;
            moData.moString.mpContent = new char[moData.moString.miLength + 1];
            if (moData.moString.mpContent == NULL)
            {
                throw;
            }
            memset(moData.moString.mpContent, 0, moData.moString.miLength + 1);
            memcpy(moData.moString.mpContent, aoString.c_str(), moData.moString.miLength);
        }
        return *this;
    }
};

#endif//__DATA_TYPE_H_
