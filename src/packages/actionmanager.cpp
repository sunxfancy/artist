/* 
* @Author: sxf
* @Date:   2015-05-28 23:21:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 20:42:12
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

void ActionManager::getAllAction(std::vector<const char*>& ans) {
	for (auto action : priv->action_map) 
		ans.push_back(action.first.c_str());
}

sigc::signal<void, const char*> ActionManager::signal_run_lua_code;