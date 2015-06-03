/* 
* @Author: sxf
* @Date:   2015-05-31 14:49:41
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 16:17:29
*/

#include "artistlib.h"
#include "app.h"

extern "C" {

// void LoadPackage(path)
static int LoadPackage(lua_State *L);

// void SearchPackages()
static int SearchPackages(lua_State *L);

// void AddSearchPath(path)
static int AddSearchPath(lua_State *L);

// void RemoveAllPath()
static int RemoveAllPath(lua_State *L);


// void ActiveTool(name)
static int ActiveTool(lua_State *L);

// void UnActiveTool(name)
static int UnActiveTool(lua_State *L);

// void AddToolFromJson(json_path)
static int AddToolFromJson(lua_State *L);

// void AddToolFromLua(lua_table)
static int AddToolFromLua(lua_State *L);

// void AddTool(Tool* cpointer)
static int AddTool(lua_State *L);


static const luaL_Reg artistlib[]=
{
	{"LoadPackage", LoadPackage},
	{"SearchPackages", SearchPackages},
	{"AddSearchPath", AddSearchPath},
	{"RemoveAllPath", RemoveAllPath},

	{"ActiveTool", ActiveTool},
	{"UnActiveTool", UnActiveTool},
	{"AddToolFromJson", AddToolFromJson},
	{"AddToolFromLua", AddToolFromLua},
	{"AddTool", AddTool},

	{NULL, NULL}
};

static int luaopen_artistlib(lua_State *L)
{
	luaL_newlib(L, artistlib);
	return 1;
};




static int LoadPackage(lua_State *L) {
	const char* str = lua_tostring(L,-1);
	PackageManager* p = App::getPackageManager();
	p->LoadPackage(str);
	lua_pop(L,1);
	return 0;
}

static int SearchPackages(lua_State *L) {
	PackageManager* p = App::getPackageManager();
	p->Search();
	return 0;
}

static int AddSearchPath(lua_State *L) {
	const char* str = lua_tostring(L,-1);
	PackageManager* p = App::getPackageManager();
	p->addSearchPath(str);
	lua_pop(L,1);
	return 0;
}

static int RemoveAllPath(lua_State *L) {
	PackageManager* p = App::getPackageManager();
	p->removeAllPath();
	return 0;
}


static int ActiveTool(lua_State *L) {
	const char* name = lua_tostring(L,-1);
	Tools* t = App::getTools();
	t->Active(name);
	lua_pop(L,1);
	return 0;
}

static int UnActiveTool(lua_State *L) {
	const char* name = lua_tostring(L,-1);
	Tools* t = App::getTools();
	t->UnActive(name);
	lua_pop(L,1);
	return 0;
}

static int AddToolFromJson(lua_State *L) {
	const char* json_path = lua_tostring(L,-1);
	Tools* t = App::getTools();
	t->AddToolFromJson(json_path);
	lua_pop(L,1);
	return 0;
}


static int AddToolFromLua(lua_State *L) {
	const char* name = lua_tostring(L,-4);
	Tool* tool = new Tool(name);
	
}

static int AddTool(lua_State *L) {
	
}


}  /// C function end

void open_artistlib(lua_State* L) {
	luaL_requiref(L, "artist_package", luaopen_artistlib, 1);
	lua_pop(L, 1);  /* remove lib */
}