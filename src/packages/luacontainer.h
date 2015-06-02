/* 
* @Author: sxf
* @Date:   2015-05-29 10:08:40
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 20:34:18
*/

#ifndef LUACONTAINER_H
#define LUACONTAINER_H

class LuaContainer_private;

/**
 * @brief 这是一个负责异步执行lua代码的类
 */
class LuaContainer
{
public:
	LuaContainer();
	~LuaContainer();

	// 这几个方法是线程安全的

	/**
	 * @brief 执行一个lua文件，需要传入一个完整路径或相对路径
	 * @param filename 路径字符串
	 */
	void RunLuafile(const char* filename);

	/**
	 * @brief 执行一段lua代码，暂时未写缓存机制，就是简单的解析执行
	 * @param code 代码数据
	 */
	void RunLuaCode(const char* code);

	/**
	 * @brief 创建一个新线程，并运转lua的控制台，会不断的从前面方法发过来的消息中取数据并进行执行
	 */
	void RunLuaShell();
protected:
	LuaContainer_private* priv;
};


#endif // LUACONTAINER_H
