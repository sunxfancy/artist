/* 
* @Author: sxf
* @Date:   2015-05-28 23:34:34
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-09 22:51:23
*/

#include "ui/myarea.h"
#include "math.h"

class MyArea_private
{
public:
	MyArea_private();
	~MyArea_private();

	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
	Glib::RefPtr< Gdk::Pixbuf > pixbuf;
};

MyArea::MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::DrawingArea(cobject)
{
	priv = new MyArea_private();
	set_size_request(800,640);
	set_events( Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
	show();
}

MyArea::~MyArea() {
	delete priv;
}

void MyArea::set_pixbuf(Gdk::Pixbuf* data) {
	priv->pixbuf = Glib::RefPtr<Gdk::Pixbuf>(data);
	signal_draw().connect( sigc::mem_fun(
		*priv, &MyArea_private::on_draw) );
}

void MyArea::update() {
	queue_draw_area(0, 0, 800, 600);
}

MyArea_private::MyArea_private() {
	
}

MyArea_private::~MyArea_private() {
	
}

bool MyArea_private::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	if (pixbuf == 0) return false;
	cr->set_source_rgba(0xff, 0xff, 0xff, 0xff);
	cr->rectangle(0, 0, 800, 640);
	cr->fill();
	Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
	cr->paint();
	cr->stroke();
	return true;
}