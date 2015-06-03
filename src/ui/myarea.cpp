/* 
* @Author: sxf
* @Date:   2015-05-28 23:34:34
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 20:37:21
*/

#include "ui/myarea.h"

class MyArea_private
{
public:
	MyArea_private();
	~MyArea_private();
};

MyArea::MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::DrawingArea(cobject)
{
	priv = new MyArea_private();
	set_size_request(800,640);
	set_events( Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
}

MyArea::~MyArea() {
	delete priv;
}

MyArea_private::MyArea_private() {
	
}

MyArea_private::~MyArea_private() {
	
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	
	return true;
}