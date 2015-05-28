/* 
* @Author: sxf
* @Date:   2015-05-28 23:21:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-28 23:33:16
*/

#include "actionmanager.h"


class ActionManager_private
{
public:
	ActionManager_private();
	~ActionManager_private();
	
};

ActionManager::ActionManager() {
	priv = new ActionManager_private();
}

ActionManager::~ActionManager() {
	delete priv;
}

ActionManager_private::ActionManager_private() {
	
}

ActionManager_private::~ActionManager_private() {
	
}