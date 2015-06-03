/* 
* @Author: sxf
* @Date:   2015-05-29 10:08:40
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 16:28:49
*/

#ifndef LUACONTAINER_H
#define LUACONTAINER_H

struct lua_State;
typedef struct lua_State lua_State;	// 希望避免对lua库的引用
typedef void (*task_CFunction) (lua_State*, void*); // 这里传入的lua的L指针和此时的参数对象

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
	void RunLuaFile(const char* filename);

	/**
	 * @brief 执行一段lua代码，暂时未写缓存机制，就是简单的解析执行
	 * @param code 代码数据
	 */
	void RunLuaCode(const char* code);

	/**
	 * @brief 在后台lua线程执行一段C函数
	 * @param cfunc C函数指针
	 * @param args 可以传入的参数
	 */
	void RunTask(task_CFunction cfunc, void* args);

	/**
	 * @brief (暂时不可用) 执行一个lua函数，传入的参数仅支持基本变量，类型需要用字符串的形式定义出来，异步执行，暂不支持返回值。
	 * @param funcname 要执行的lua函数名
	 * @param type 类型描述字符串 i -> int, d->double, f->function, s->const char*, b->bool
	 */
	void RunLuaFunc(const char* funcname, const char* type, ...);

	/**
	 * @brief 创建一个新线程，并运转lua的控制台，会不断的从前面方法发过来的消息中取数据并进行执行
	 */
	void RunLuaShell();
protected:
	LuaContainer_private* priv;
};


#endif // LUACONTAINER_H
