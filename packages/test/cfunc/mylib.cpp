/* 
* @Author: sxf
* @Date:   2015-05-30 20:47:20
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-30 21:25:17
*/

#include <iostream>
#include "lua.hpp"

extern "C" {

static int l_hello(lua_State* l)
{
    printf("Hello, world!\n");
    return 0;
}

static int displayLuaFunction(lua_State *l)
{
    // number of input arguments
    int argc = lua_gettop(l);
    // print input arguments
    std::cout << "[C++] Function called from Lua with " << argc
              << " input arguments" << std::endl;
    for(int i=0; i<argc; i++)
    {
        std::cout << " input argument #" << argc-i << ": "
                  << lua_tostring(l, lua_gettop(l)) << std::endl;
        lua_pop(l, 1);
    }
    // push to the stack the multiple return values
    std::cout << "[C++] Returning some values" << std::endl;
    lua_pushnumber(l, 12);
    lua_pushstring(l, "See you space cowboy");
    // number of return values
    return 2;
}

static const luaL_Reg mylib[]=
{
	{"l_hello", l_hello},
    {"displayLuaFunction", displayLuaFunction},
    {NULL, NULL}
};

int luaopen_mylib(lua_State *L)
{
	printf("mylib loaded\n");
	luaL_newlib(L, mylib);
	return 1;
};

}