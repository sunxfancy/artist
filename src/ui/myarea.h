/* 
* @Author: sxf
* @Date:   2015-05-28 23:33:35
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-28 23:35:42
*/

#ifndef MYAREA_H
#define MYAREA_H

#include <gtkmm.h>

class MyArea_private;
class MyArea : public Gtk::DrawingArea
{
public:
	MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	~MyArea();
protected:
	MyArea_private* priv;
};


#endif // MYAREA_H
