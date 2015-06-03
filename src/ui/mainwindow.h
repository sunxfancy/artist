/* 
* @Author: sxf
* @Date:   2015-05-28 18:55:35
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 20:03:32
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include "ui/myarea.h"

class MainWindow_private;

/**
 * @brief 主界面类
 */
class MainWindow : public Gtk::Window
{
public:
	/**
	 * @brief 通过builder构造窗口
	 */
	MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
	virtual ~MainWindow();

	/**
	 * @brief 获取一个绘图控件
	 */
	MyArea* getMyArea();

	void gtkActionRunCode(const char* name, const char* code);

	void gtkActionRunAction(const char* name, const char* action);

	/**
	 * @brief 创建该窗体的唯一方法
	 */
	static MainWindow* CreateFromBuilder();
protected:
	MainWindow_private* priv;
};

#endif // MAINWINDOW_H
