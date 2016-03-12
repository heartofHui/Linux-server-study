#include <iostream>
#include <string>
#include <stdio.h>
#include "json/json.h"

using namespace std;

int main()
{
    const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

    Json::Reader reader;
    Json::Value root;
    if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
    {
     std::string upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"
     int code = root["code"].asInt();    // 访问节点，code = 100
     cout<<"code:"<<code<<endl;
     cout<<"upload:"<<upload_id<<endl;
    }

    Json::Value testRoot;
    Json::Value jsontmp;
    Json::FastWriter fast_writer;
    jsontmp["name"]=Json::Value("chenhui");
    jsontmp["age"]=Json::Value(123);
    jsontmp["address"]=Json::Value("beijing");

    testRoot["family"]=Json::Value("Chen&Zhang");
    testRoot["number"]=Json::Value(2);
    testRoot["people"]=jsontmp;
    testRoot["sex"].append("boy");
    testRoot["sex"].append("girl");
    testRoot["sex"].append(2);
    string ss="test";
	testRoot["test"]=Json::Value(ss);
	string txt=fast_writer.write(testRoot);
    cout<<"jsontxt: "<<txt<<endl;
    return 0;
}
