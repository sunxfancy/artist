/* 
* @Author: sxf
* @Date:   2015-06-01 15:56:55
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-09 23:34:33
*/

#include "tools/tool.h"
#include "utils/fileloader.h"
#include "app.h"
#include "cJSON.h"
#include <string>

class Tool_private
{
public:
	std::string name;

	t_mouse_hook m_mouse_click;
	t_mouse_hook m_mouse_move;
	t_mouse_hook m_mouse_release;

	int d_time;
	guint32 last_time;

	bool is_alltime_listen_move;
	bool is_clicked;
	
	bool on_mouseclick(GdkEventButton* p);
	bool on_mouserelease(GdkEventButton* p);
	bool on_mousemove(GdkEventMotion* p);
};

Tool::Tool(const char* name) {
	priv = new Tool_private();
	if (name) priv->name = name;
	priv->is_alltime_listen_move = priv->is_clicked = false;
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

int Tool::getDeltaTime() {
	return priv->d_time;
}

void Tool::set_is_alltime_listen_move(bool b) {
	priv->is_alltime_listen_move = b;
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
	if (!is_alltime_listen_move) is_clicked = true;
	d_time = 0;
	return m_mouse_click.emit(p->x, p->y);
}

bool Tool_private::on_mouserelease(GdkEventButton* p) {
	if (!is_alltime_listen_move) is_clicked = false;
	d_time = p->time - last_time;
	last_time = p->time;
	return m_mouse_release.emit(p->x, p->y);
}

static void
print_axes (GdkDevice *device, gdouble *axes)
{
	int i;
	if (axes) {
		g_print ("%s ", gdk_device_get_name(device));
		for (i = 0; i < gdk_device_get_n_axes(device); i++) 
			g_print ("%g ", axes[i]);
		g_print ("\n");
	}
}

bool Tool_private::on_mousemove(GdkEventMotion* p) {
	double press = 0;
	GdkDevice* d = gdk_event_get_source_device((GdkEvent*)p);
	print_axes (p->device, p->axes);
	gdk_event_get_axis ((GdkEvent*)p, GDK_AXIS_LAST, &press);

	// gdk_device_get_axis (d, NULL, GDK_AXIS_PRESSURE, &press);

	printf("%s\n", gdk_device_get_name (d));
	printf("X: %f\tY: %f\t PRESS: %f\n", p->x, p->y, press);
	if (is_alltime_listen_move || is_clicked) {
		d_time = p->time - last_time;
		last_time = p->time;
		return m_mouse_move.emit(p->x, p->y);
	}
	else return false;
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