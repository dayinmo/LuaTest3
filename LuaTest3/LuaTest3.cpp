#include "stdafx.h"
#include <iostream>  
#include <string.h> 
#include <stdio.h>  
using namespace std;

extern "C" {
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"  
}

/* 指向Lua解释器的指针 */
static int average(lua_State *L)
{
	/* 得到参数个数 */
	int n = lua_gettop(L);
	double sum = 0;
	int i;

	/* 循环求参数之和 */
	for (i = 1; i <= n; i++)
	{
		/* 求和 */
		sum += lua_tonumber(L, i);
	}
	/* 压入平均值 */
	lua_pushnumber(L, sum / n);
	/* 压入和 */
	lua_pushnumber(L, sum);
	/* 返回返回值的个数 */
	return 2;
}

int main(int argc, char *argv[])
{
	lua_State *L = luaL_newstate();
	/* 初始化Lua */
	//这句可以不要
	//L = lua_open();

	/* 载入Lua基本库 */
	luaL_openlibs(L);
	/* 注册函数 */
	lua_register(L, "average", average);
	/* 运行脚本 */
	luaL_dofile(L, "hello.lua");
	/* 清除Lua */
	lua_close(L);

	/* 暂停 */
	printf("Press enter to exit…");
	getchar();
	return 0;
}