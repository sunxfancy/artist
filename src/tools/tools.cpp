/* 
* @Author: sxf
* @Date:   2015-06-01 15:54:12
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 15:07:14
*/

#include "tools.h"
#include <map>
#include <string>
#include <string.h>
using namespace std;

class Tools_private
{
public:
	Tools_private();
	~Tools_private();
	map<string, Tool*> tools_map;
	Tool* active_tool;
};

Tools::Tools() {
	priv = new Tools_private();
}

Tools::~Tools() {
	delete priv;
}

void Tools::Active(const char* tool_name) {
	auto t  = priv->tools_map.find(tool_name);
	if ( t != priv->tools_map.end() ) {
		if (priv->active_tool) 
			priv->active_tool->UnActive();
		priv->active_tool = t->second;
		priv->active_tool->Active();
	}
}

void Tools::UnActive(const char* tool_name) {
	if ( strcmp(priv->active_tool->getName(), tool_name) == 0 ) {
		priv->active_tool->UnActive();
		priv->active_tool = NULL;
	}
}

void Tools::AddToolFromJson(const char* json_path) {
	Tool* tool = Tool::create_from_json(json_path);
	priv->tools_map[ tool->getName() ] = tool;
}

void Tools::AddTool(Tool* tool) {
	priv->tools_map[ tool->getName() ] = tool;
}


Tools_private::Tools_private() {
	
}

Tools_private::~Tools_private() {
	
}