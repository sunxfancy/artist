/* 
* @Author: sxf
* @Date:   2015-05-28 23:34:34
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-31 21:55:10
*/

#include "myarea.h"

class MyArea_private
{
public:
	MyArea_private();
	~MyArea_private();

	bool on_mouseclick(GdkEventButton* p);
	bool on_mouserelease(GdkEventButton* p);
	bool on_mousemove(GdkEventMotion* p);
};

MyArea::MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::DrawingArea(cobject)
{
	priv = new MyArea_private();
	set_size_request(800,640);
	set_events( Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
	signal_button_release_event().connect(
		sigc::mem_fun(*priv, &MyArea_private::on_mouseclick));
	signal_button_release_event().connect(
		sigc::mem_fun(*priv, &MyArea_private::on_mouserelease));
	signal_motion_notify_event ().connect(
		sigc::mem_fun(*priv, &MyArea_private::on_mousemove));
}

MyArea::~MyArea() {
	delete priv;
}

MyArea_private::MyArea_private() {
	
}

MyArea_private::~MyArea_private() {
	
}

bool MyArea_private::on_mouseclick(GdkEventButton* p) {

	return false;
}

bool MyArea_private::on_mouserelease(GdkEventButton* p) {

	return false;
}

bool MyArea_private::on_mousemove(GdkEventMotion* p) {

	return false;
}