/* 
* @Author: sxf
* @Date:   2015-06-01 14:02:32
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 14:57:26
*/
#ifndef TOOLS_H
#define TOOLS_H

#include "tool.h"

class Tools_private;
class Tools
{
public:
	Tools();
	~Tools();

	void Active(const char* tool_name);
	void UnActive(const char* tool_name);

	void AddToolFromJson(const char* json_path);
	void AddTool(Tool* tool);
protected:
	Tools_private* priv;
};


#endif // TOOLS_H
