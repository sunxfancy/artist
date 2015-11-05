/* 
* @Author: sxf
* @Date:   2015-05-28 23:33:35
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-08 17:18:27
*/

#ifndef MYAREA_H
#define MYAREA_H

#include <gtkmm.h>

class MyArea_private;

/**
 * @brief 自定义的绘图区域，复制将图像绘制出来
 */
class MyArea : public Gtk::DrawingArea
{
public:
	MyArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~MyArea();

	void update();
	void set_pixbuf(Gdk::Pixbuf* data);
protected:
	MyArea_private* priv;
};


#endif // MYAREA_H
