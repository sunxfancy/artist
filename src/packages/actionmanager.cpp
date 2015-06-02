/* 
* @Author: sxf
* @Date:   2015-05-28 23:21:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 17:04:11
*/

#include "actionmanager.h"
#include <map>
#include <string>
#include "app.h"

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

void ActionManager::RegisterAction(const char* name, const char* code) {
	priv->action_map[name] = code;
}

void ActionManager::Do(const char* name) {
	LuaContainer* lua = App::getLuaContainer();
	auto p = priv->action_map.find(name);
	if (p != priv->action_map.end())
		lua->RunLuaCode(p->second.c_str());
	else
		printf("Error: Can't find the Action [ %s ]\n", name);
}
