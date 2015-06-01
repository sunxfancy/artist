/* 
* @Author: sxf
* @Date:   2015-05-29 10:08:40
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-29 16:16:38
*/

#ifndef LUACONTAINER_H
#define LUACONTAINER_H

class LuaContainer_private;
class LuaContainer
{
public:
	LuaContainer();
	~LuaContainer();

	// 这几个方法是线程安全的
	void RunLuafile(const char* filename);
	void RunLuaCode(const char* code);
	void RunLuaShell(); // 创建一个新线程,运转lua的控制台
protected:
	LuaContainer_private* priv;
};


#endif // LUACONTAINER_H
