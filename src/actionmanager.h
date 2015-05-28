/* 
* @Author: sxf
* @Date:   2015-05-28 23:20:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-28 23:21:20
*/

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

class ActionManager_private;
class ActionManager
{
public:
	ActionManager();
	~ActionManager();
protected:
	ActionManager_private* priv;
};


#endif // ACTIONMANAGER_H
