/* 
* @Author: sxf
* @Date:   2015-06-03 19:08:04
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 19:41:04
*/

#ifndef ACTIONPROXY_H
#define ACTIONPROXY_H

#include <sigc++/sigc++.h>
#include <string>

class ActionProxy
{
public:
	ActionProxy(std::string str, bool is_code = false);
	~ActionProxy();

	void Activate();

	static sigc::signal<void, const char*> signal_action_do;
	static sigc::signal<void, const char*> signal_run_lua_code;
protected:
	bool is_code;
	std::string lua_code;
	std::string action_name;
};

#endif // ACTIONPROXY_H
