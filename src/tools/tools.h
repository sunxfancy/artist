/* 
* @Author: sxf
* @Date:   2015-06-01 14:02:32
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 21:03:13
*/
#ifndef TOOLS_H
#define TOOLS_H

#include "tools/tool.h"

class Tools_private;

/**
 * @brief 这是全部工具的容器类
 */
class Tools
{
public:
	Tools();
	~Tools();

	/**
	 * @brief 激活该工具，同时反激活原来激活中的工具
	 * @param tool_name 工具的注册名称
	 */
	void Active(const char* tool_name);

	/**
	 * @brief 主动反激活一个工具，很少被调用
	 * @param tool_name 工具的注册名称
	 */
	void UnActive(const char* tool_name);

	/**
	 * @brief 从json描述中添加一个新的工具
	 * @param json_path json的路径
	 */
	void AddToolFromJson(const char* json_path);

	/**
	 * @brief 添加一个已经构建好的工具
	 * @param tool 该工具实例化后的指针
	 */
	void AddTool(Tool* tool);

protected:
	Tools_private* priv;
};


#endif // TOOLS_H
