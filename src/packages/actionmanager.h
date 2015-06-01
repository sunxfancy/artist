/* 
* @Author: sxf
* @Date:   2015-05-28 23:20:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-29 19:44:12
*/

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

// 负责将界面上以及用户键入的命令转换为lua函数进行执行

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
