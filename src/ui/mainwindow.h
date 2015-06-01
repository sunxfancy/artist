/* 
* @Author: sxf
* @Date:   2015-05-28 18:55:35
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-29 10:06:15
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow_private;
class MainWindow : public Gtk::Window
{
public:
	MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~MainWindow();

	static MainWindow* CreateFromBuilder();
protected:
	MainWindow_private* priv;
};

#endif // MAINWINDOW_H
