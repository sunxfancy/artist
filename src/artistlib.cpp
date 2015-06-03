/* 
* @Author: sxf
* @Date:   2015-05-31 14:49:41
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 21:26:29
*/

#include "artistlib.h"
#include "app.h"
#include "tools/luatool.h"

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

// void AddToolFromLua(clickfunc_name, releasefunc_name, movefunc_name)
static int AddToolFromLua(lua_State *L);

// void AddTool(Tool* cpointer)
static int AddTool(lua_State *L);


// void Register(const char* name, const char* code);
static int RegisterAction(lua_State *L);

// void Do(const char* name);
static int DoAction(lua_State *L);


//void gtkActionRunCode(const char* name, const char* code);	
static int gtkActionRunCode(lua_State* L);

//void gtkActionRunAction(const char* name, const char* action);
static int gtkActionRunAction(lua_State* L);


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
	
	{"RegisterAction", RegisterAction},
	{"DoAction", DoAction},

	{"gtkActionRunCode", gtkActionRunCode},
	{"gtkActionRunAction", gtkActionRunAction},

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
	const char* name    = lua_tostring(L,-4);
	const char* click   = lua_tostring(L,-3);
	const char* release = lua_tostring(L,-2);
	const char* move    = lua_tostring(L,-1);
	LuaTool* tool = new LuaTool(name);
	tool->set_mouse_click_lua_funcname(click);
	tool->set_mouse_release_lua_funcname(release);
	tool->set_mouse_move_lua_funcname(move);
	lua_pop(L, 4);
	Tools* t = App::getTools();
	t->AddTool(tool);
	return 0;
}

static int AddTool(lua_State *L) {
	Tool* tool = (Tool*) lua_touserdata(L, -1);
	Tools* t = App::getTools();
	t->AddTool(tool);
	lua_pop(L, 1);
	return 0;
}

static int RegisterAction(lua_State *L) {
	const char* name = lua_tostring(L, -2);
	const char* code = lua_tostring(L, -1);
	ActionManager* actionManager = App::getActionManager();
	actionManager->Register(name, code);
	lua_pop(L, 2);
	return 0;
}

static int DoAction(lua_State *L) {
	const char* name = lua_tostring(L, -1);
	ActionManager* actionManager = App::getActionManager();
	actionManager->Do(name);
	lua_pop(L, 1);
	return 0;
}

static int gtkActionRunCode(lua_State* L) {
	const char* name = lua_tostring(L, -2);
	const char* code = lua_tostring(L, -1);
	MainWindow* window = App::getMainWindow();
	window->gtkActionRunCode(name, code);
	lua_pop(L, 2);
	return 0;
}

static int gtkActionRunAction(lua_State* L) {
	const char* name = lua_tostring(L, -2);
	const char* action = lua_tostring(L, -1);
	MainWindow* window = App::getMainWindow();
	window->gtkActionRunAction(name, action);
	lua_pop(L, 2);
	return 0;
}


}  /// C function end

void open_artistlib(lua_State* L) {
	luaL_requiref(L, "artist", luaopen_artistlib, 1);
	lua_pop(L, 1);  /* remove lib */
}