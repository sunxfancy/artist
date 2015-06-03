/* 
* @Author: sxf
* @Date:   2015-05-28 23:21:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 20:32:02
*/

#include "packages/actionmanager.h"
#include <map>
#include <string>


using namespace std;

class ActionManager_private
{
public:
	map<string, string> action_map;
};

ActionManager::ActionManager() {
	priv = new ActionManager_private();
}

ActionManager::~ActionManager() {
	delete priv;
}

void ActionManager::Register(const char* name, const char* code) {
	priv->action_map[name] = code;
}

void ActionManager::Do(const char* name) {
	auto p = priv->action_map.find(name);
	if (p != priv->action_map.end())
		signal_run_lua_code.emit(p->second.c_str());
	else
		printf("Error: Can't find the Action [ %s ]\n", name);
}


sigc::signal<void, const char*> ActionManager::signal_run_lua_code;