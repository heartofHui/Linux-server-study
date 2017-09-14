#include <iostream>
#include <string>
#include <stdio.h>
#include "json/json.h"

using namespace std;


string getJsonStringValue(Json::Value &value,string colum)
{
	string defaultVal="";
	if (!value[colum].isNull() && value[colum].isString())
	{
		return value[colum].asString();
	}
	else
	{
		return defaultVal;
	}
}

int getJsonIntValue(Json::Value &value,string colum)
{
	int defaultVal=0;
	if (!value[colum].isNull() && value[colum].isInt())
	{
		return value[colum].asInt();
	}
	else
	{
		return defaultVal;
	}
}

int main()
{
	char* str =
			"{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

	Json::Reader reader;
	Json::Value root;
	if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		std::string upload_id = root["uploadid"].asString(); // 访问节点，upload_id = "UP000000"
		int code = root["code"].asInt();    // 访问节点，code = 100
		cout << "code:" << code << endl;
		cout << "upload:" << upload_id << endl;
		cout<<"-------"<<endl;
		if(!root["testss"].empty() && root["testss"].isString())
		{
			std::string ss = root["testss"].asString();
			cout << "ss:" << ss << endl;
		}
		cout<<"-------"<<endl;
	}

	Json::Value testRoot;

	Json::Value jsontmp;
	Json::Value * rootPtr = &jsontmp;
	void * testAddr = &jsontmp;
	if (jsontmp.isNull())
	{
		cout << "json is null" << endl;
	}
	Json::FastWriter fast_writer;
	jsontmp["name"] = Json::Value("chenhui");
	jsontmp["age"] = Json::Value(123);
	jsontmp["address"] = Json::Value("beijing");
//	string name="";
//	getJsonValue<string>(jsontmp, "name", "string", name);
//
//
//	cout << "name:" << name << endl;

	int age=0;
	age=getJsonIntValue(jsontmp,"age");
	cout<<"age:"<<age<<endl;

	//Json::Value tmp=rootPtr;
	string sss = jsontmp["name"].asString();
	cout << (*rootPtr)["name"].asString() << endl;
	cout << (*((Json::Value *) testAddr))["name"].asString() << endl;

	testRoot["family"] = Json::Value("Chen&Zhang");
	testRoot["number"] = Json::Value(2);
	testRoot["people"] = jsontmp;
	testRoot["sex"].append("boy");
	testRoot["sex"].append("girl");
	testRoot["sex"].append(2);
	string ss = "test";
	testRoot["test"] = Json::Value(ss);
	
	string testKey = "chenhui";
	testRoot[testKey] = Json::Value("ddddas");
	

	testRoot["chenarr"].append(jsontmp);
	
	const char *txt;
	txt = fast_writer.write(testRoot).c_str();
	cout << "jsontxt: " << txt << endl;


	return 0;
}


