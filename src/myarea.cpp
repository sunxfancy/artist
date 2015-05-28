/* 
* @Author: sxf
* @Date:   2015-05-28 23:34:34
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-28 23:36:29
*/

#include "myarea.h"

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
}

MyArea::~MyArea() {
	delete priv;
}

MyArea_private::MyArea_private() {
	
}

MyArea_private::~MyArea_private() {
	
}