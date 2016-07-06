//g++ luaTest.cpp -L. -llua -Ilua -o luatest
#include <iostream>
#include <string.h>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
};
using namespace std;

int main()
{
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return 0;
    }
    //load lua file
    int ret=luaL_loadfile(L,"hello.lua");
    if(ret)
    {
        cout<<"load file error"<<endl;
        return 0;
    }
    ret=lua_pcall(L,0,0,0);
    if(ret)
    {
        cout<<"pcall error"<<endl;
        return 0;
    }
    //read
    lua_getglobal(L, "str");
    string str = lua_tostring(L, -1);
    cout<<"str="<<str<<endl;
    //read table
    lua_getglobal(L,"tbl");
    lua_getfield(L,-1,"name");
    str=lua_tostring(L,-1);
    cout<<"tbl:name"<<str.c_str()<<endl;

    //read function
    lua_getglobal(L, "add");//获取函数，压入栈中
    lua_pushnumber(L, 10);   //压入第一个参数
    lua_pushnumber(L, 20);   //压入第二个参数
    int iret=lua_pcall(L, 2, 1, 0);

    if(iret)
    {
        const char * perrormsg=lua_tostring(L,-1);
        cout<<perrormsg<<endl;
        lua_close(L);
        return 0;
    }
    if(lua_isnumber(L, -1))
    {
        double fvalue=lua_tonumber(L,-1);
        cout<<"result is:"<<fvalue<<endl;
    }
    lua_close(L);
    return 0;
}
