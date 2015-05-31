/* 
* @Author: sxf
* @Date:   2015-05-28 18:56:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-29 19:02:58
*/

#include "mainwindow.h"
#include "myarea.h"
#include <iostream>

class MainWindow_private
{
public:
	MainWindow_private();
	~MainWindow_private();

	Gtk::Toolbar* mp_toolbar;
	MyArea* mp_area;
	Glib::RefPtr<Gtk::Action> mp_new_file_action;
	void on_new_file_clicked();
};

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::Window(cobject)
{
	priv = new MainWindow_private();
	builder->get_widget("toolbar", priv->mp_toolbar);
	builder->get_widget_derived<MyArea>("drawing_area", priv->mp_area);

	priv->mp_new_file_action = Glib::RefPtr<Gtk::Action>::cast_dynamic(
		builder->get_object("new_file_action"));

	if (priv->mp_new_file_action) {
		priv->mp_new_file_action->signal_activate().connect(
			sigc::mem_fun(*priv, &MainWindow_private::on_new_file_clicked) );
	}
}

MainWindow::~MainWindow() {
	delete priv;
}



MainWindow* MainWindow::CreateFromBuilder() {
	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try
	{
		refBuilder->add_from_file("res/mainwindow.glade");
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		return NULL;
	}
	catch(const Glib::MarkupError& ex)
	{
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return NULL;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return NULL;
	}
	MainWindow* pWindow = NULL;
	refBuilder->get_widget_derived<MainWindow>("mainwindow", pWindow);
	return pWindow;
}

MainWindow_private::MainWindow_private() {

}

MainWindow_private::~MainWindow_private() {

}

void MainWindow_private::on_new_file_clicked() {
	printf("hello glade\n");
}