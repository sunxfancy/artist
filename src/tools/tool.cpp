/* 
* @Author: sxf
* @Date:   2015-06-01 15:56:55
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 21:35:54
*/

#include "tool.h"
#include <string>
#include "app.h"
#include "fileloader.h"
#include "cJSON.h"

class Tool_private
{
public:
	std::string name;

	t_mouse_hook m_mouse_click;
	t_mouse_hook m_mouse_move;
	t_mouse_hook m_mouse_release;
	
	bool on_mouseclick(GdkEventButton* p);
	bool on_mouserelease(GdkEventButton* p);
	bool on_mousemove(GdkEventMotion* p);
};

Tool::Tool(const char* name) {
	priv->name = name;
	priv = new Tool_private();
}

Tool::~Tool() {
	delete priv;
}

const char* Tool::getName() const {
	return priv->name.c_str();
}

void Tool::Active() {
	MyArea* myArea = App::getMyArea();

	myArea->signal_button_press_event().connect(
		sigc::mem_fun(*priv, &Tool_private::on_mouseclick));
	myArea->signal_button_release_event().connect(
		sigc::mem_fun(*priv, &Tool_private::on_mouserelease));
	myArea->signal_motion_notify_event ().connect(
		sigc::mem_fun(*priv, &Tool_private::on_mousemove));
}

void Tool::UnActive() {

}

t_mouse_hook Tool::signal_mouse_click() const {
	return priv->m_mouse_click;
}

t_mouse_hook Tool::signal_mouse_move() const {
	return priv->m_mouse_move;
}

t_mouse_hook Tool::signal_mouse_release() const {
	return priv->m_mouse_release;
}

bool Tool_private::on_mouseclick(GdkEventButton* p) {
	return m_mouse_click.emit(p->x, p->y);
}

bool Tool_private::on_mouserelease(GdkEventButton* p) {
	return m_mouse_release.emit(p->x, p->y);
}

bool Tool_private::on_mousemove(GdkEventMotion* p) {
	return m_mouse_move.emit(p->x, p->y);
}

Tool* Tool::create_from_json(const char* path) {
	char* data = FileLoader::load(path);
	cJSON* cj = cJSON_Parse(data);
	if (!cj) { printf("error json format\n"); return NULL; }

	cJSON* name_j = cJSON_GetObjectItem(cj, "name");
	char* name = NULL;
	if (name_j) {
		name = name_j->valuestring;
	} 
	cJSON_Delete(cj);
	delete data;

	Tool* t = new Tool(name);
	return t;
}