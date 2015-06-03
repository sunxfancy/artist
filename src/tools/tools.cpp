/* 
* @Author: sxf
* @Date:   2015-06-01 15:54:12
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 21:58:32
*/

#include "tools/tools.h"
#include <map>
#include <string>
#include <string.h>
#include "tools/brush.h"

using namespace std;

class Tools_private
{
public:
	map<string, Tool*> tools_map;
	Tool* active_tool;
	
	static Tool* default_tools[];
};

Tool* Tools_private::default_tools[] = {
	new Brush(), 
	NULL
};

Tools::Tools() {
	priv = new Tools_private();
	for (Tool** t = priv->default_tools; *t != NULL; ++t)
		AddTool(*t);
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
