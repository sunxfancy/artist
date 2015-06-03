/* 
* @Author: sxf
* @Date:   2015-06-03 12:52:12
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 16:35:52
*/

#ifndef LUATOOL_H
#define LUATOOL_H

#include "tools/tool.h"
#include "packages/luacontainer.h"

class LuaTool_private;
class LuaTool : public Tool
{
public:
	LuaTool(const char* name);
	~LuaTool();

	static sigc::signal<void, task_CFunction, void*> signal_run_task;
protected:
	LuaTool_private* priv;
};


#endif // LUATOOL_H
