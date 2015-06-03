/* 
* @Author: sxf
* @Date:   2015-06-03 19:25:38
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 19:41:45
*/

#include "ui/actionproxy.h"

ActionProxy::ActionProxy(std::string str, bool _is_code) {
	is_code = _is_code;
	if (is_code) lua_code = str;
	else action_name = str;
}

ActionProxy::~ActionProxy() {

}


void ActionProxy::Activate() {
	if (is_code) signal_run_lua_code.emit(lua_code.c_str());
	else signal_action_do.emit(action_name.c_str());
}

sigc::signal<void, const char*> ActionProxy::signal_action_do;
sigc::signal<void, const char*> ActionProxy::signal_run_lua_code;