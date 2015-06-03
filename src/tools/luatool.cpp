/* 
* @Author: sxf
* @Date:   2015-06-03 12:53:58
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 17:01:00
*/

#include "tools/luatool.h"
#include "lua.hpp"
#include <string>

class LuaTool_private
{
public:
	bool mouse_click(double, double);
	bool mouse_release(double, double);
	bool mouse_move(double, double);

	void run_lua_func(const char* funcname, double x, double y);

	std::string mouse_click_lua_funcname;
	std::string mouse_release_lua_funcname;
	std::string mouse_move_lua_funcname;
};

LuaTool::LuaTool(const char* name)
	: Tool(name)
{
	priv = new LuaTool_private();

	signal_mouse_click().connect(
		sigc::mem_fun(*priv, &LuaTool_private::mouse_click));
	signal_mouse_move().connect(
		sigc::mem_fun(*priv, &LuaTool_private::mouse_move));
	signal_mouse_release().connect(
		sigc::mem_fun(*priv, &LuaTool_private::mouse_release));
}

LuaTool::~LuaTool() {
	delete priv;
}

typedef struct _lua_call2d {
	std::string funcname;
	double x, y;
} lua_call2d;

static void run_lua_call2d(lua_State* L, void* data) {
	lua_call2d* pd = (lua_call2d*)data;
	lua_getglobal(L, pd->funcname.c_str()); /* get the function by name */
	if(!lua_isfunction(L,-1)) {
		lua_pop(L,1); delete pd; return;
	}
	lua_pushnumber(L, pd->x);   /* push 1st argument */
	lua_pushnumber(L, pd->y);   /* push 2nd argument */
	if (lua_pcall(L, 2, 0, 0) != 0) {
		printf("error running function '%s': %s\n",pd->funcname.c_str(), lua_tostring(L, -1)); 
		lua_pop(L,1); delete pd; return;
	}
	delete pd; // 一定注意不要漏内存
}

void LuaTool_private::run_lua_func(const char* funcname, double x, double y) {
	lua_call2d* pd = new lua_call2d();
	pd->funcname = funcname; pd->x = x; pd->y = y;
	LuaTool::signal_run_task.emit(run_lua_call2d, pd);
}

bool LuaTool_private::mouse_click(double x, double y) {
	if (!mouse_click_lua_funcname.empty())
		run_lua_func(mouse_click_lua_funcname.c_str(), x, y);
	return false;
}

bool LuaTool_private::mouse_release(double x, double y) {
	if (!mouse_release_lua_funcname.empty())
		run_lua_func(mouse_release_lua_funcname.c_str(), x, y);
	return false;
}

bool LuaTool_private::mouse_move(double x, double y) {
	if (!mouse_move_lua_funcname.empty())
		run_lua_func(mouse_move_lua_funcname.c_str(), x, y);
	return false;
}

sigc::signal<void, task_CFunction, void*> LuaTool::signal_run_task;