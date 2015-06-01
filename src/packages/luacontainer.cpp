/* 
* @Author: sxf
* @Date:   2015-05-29 10:09:39
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 15:23:10
*/

#include "luacontainer.h"
#include <lua.hpp>
#include <glibmm/threads.h>
#include <glibmm/thread.h>
#include "msg.h"
#include "artistlib.h"
#include <queue>
#include <string.h>

class LuaContainer_private
{
public:
	LuaContainer_private();
	~LuaContainer_private();
	
	void init();
	inline void run_file(const char* filename);
	inline void run_code(const char* code);

	lua_State* L = NULL;
	std::queue<msg> Q;

	Glib::Cond cond;
	Glib::Mutex mutex;
};

LuaContainer::LuaContainer() {
	priv = new LuaContainer_private();
}

LuaContainer::~LuaContainer() {
	delete priv;
}

void LuaContainer::RunLuafile(const char* filename) {
	priv-> mutex.lock();
	printf("%s\n", filename);
	priv-> Q.push(msg(1, filename));
	priv-> cond.signal();
	priv-> mutex.unlock();
}

void LuaContainer::RunLuaCode(const char* code) {
	priv-> mutex.lock();
	priv-> Q.push(msg(2, code));
	priv-> cond.signal();
	priv-> mutex.unlock();
}

void LuaContainer::RunLuaShell() {
	priv->L = luaL_newstate();
	luaL_openlibs (priv->L);
	open_artistlib(priv->L);
	Glib::Threads::Thread::create( sigc::mem_fun(*priv, &LuaContainer_private::init) );
}

LuaContainer_private::LuaContainer_private() {
	
}

LuaContainer_private::~LuaContainer_private() {
	
}

void LuaContainer_private::init() {
	while(1) {
		mutex.lock();
		if (Q.empty()) cond.wait(mutex);
		
		msg m = Q.front();
		Q.pop();
		mutex.unlock();

		if (m.type == 1) run_file(m.data.c_str());
		if (m.type == 2) run_code(m.data.c_str());
	}
}

void LuaContainer_private::run_file(const char* filename) {
	int error = luaL_loadfile(L, filename) | lua_pcall(L, 0, 0, 0);
	if (error) {
		printf("Omg 怎么回事啊\n");
		printf("%s\n", filename);
		printf("%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);/* pop error message from the stack */
	}
}

void LuaContainer_private::run_code(const char* code) {
	int error = luaL_loadbuffer(L, code, strlen(code) ,"chunk") //加载当前script
                | lua_pcall(L, 0, 0, 0); // 巧妙的利用或运算符，前面若成功返回0，则执行后面的
	if (error) {
		printf("%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);/* pop error message from the stack */
	}
}
