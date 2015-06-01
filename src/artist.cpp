/* 
* @Author: sxf
* @Date:   2015-05-31 14:49:41
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 14:35:50
*/

#include "artistlib.h"
#include "app.h"

extern "C" {

static int LoadPackage(lua_State *L);
static int SearchPackages(lua_State *L);
static int AddSearchPath(lua_State *L);
static int RemoveAllPath(lua_State *L);

static const luaL_Reg artistlib[]=
{
	{"LoadPackage", LoadPackage},
	{"SearchPackages", SearchPackages},
	{"AddSearchPath", AddSearchPath},
	{"RemoveAllPath", RemoveAllPath},
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


}

void open_artistlib(lua_State* L) {
	luaL_requiref(L, "artist_package", luaopen_artistlib, 1);
	lua_pop(L, 1);  /* remove lib */
}