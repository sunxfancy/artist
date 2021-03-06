/* 
* @Author: sxf
* @Date:   2015-06-01 15:56:09
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-08 11:13:44
*/

#ifndef TOOL_H
#define TOOL_H

#include <sigc++/sigc++.h> 
typedef sigc::signal<bool, double, double> t_mouse_hook;

class Tool_private;
class Tool
{
public:
	Tool(const char* name);
	~Tool();

	const char* getName() const;
	void Active();
	void UnActive();
	void set_is_alltime_listen_move(bool b);
	int getDeltaTime();
	
	t_mouse_hook signal_mouse_click() const;
	t_mouse_hook signal_mouse_move() const;
	t_mouse_hook signal_mouse_release() const;

	static Tool* create_from_json(const char* path);
protected:
	Tool_private* priv;
};


#endif // TOOL_H
