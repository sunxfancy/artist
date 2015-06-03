/* 
* @Author: sxf
* @Date:   2015-05-28 23:20:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 20:39:34
*/

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <sigc++/sigc++.h> 
#include <vector>
// 负责将界面上以及用户键入的命令转换为lua函数进行执行

class ActionManager_private;
class ActionManager
{
public:
	ActionManager();
	~ActionManager();

	void Register(const char* name, const char* code);
	void Do(const char* name);

	void getAllAction(std::vector<const char*>&);

	static sigc::signal<void, const char*> signal_run_lua_code;
protected:
	ActionManager_private* priv;
};


#endif // ACTIONMANAGER_H
