/* 
* @Author: sxf
* @Date:   2015-05-28 18:56:36
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 21:21:35
*/

#include "ui/mainwindow.h"
#include "ui/actionproxy.h"
#include <iostream>
#include <list>

class MainWindow_private
{
public:
	MainWindow_private(const Glib::RefPtr<Gtk::Builder>& builder);
	~MainWindow_private();

	Gtk::Toolbar* mp_toolbar;
	MyArea* mp_area;
	std::list< Glib::RefPtr<Gtk::Action> > mp_action_list;
	std::list< ActionProxy* > mp_proxy_list;
	void map_action2data(const char* name, const char* data, bool is_code);
	const Glib::RefPtr<Gtk::Builder> m_builder;
};

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::Window(cobject)
{
	priv = new MainWindow_private(builder);
	builder->get_widget("toolbar", priv->mp_toolbar);
	builder->get_widget_derived<MyArea>("drawing_area", priv->mp_area);

	set_events( Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK );
}

MainWindow::~MainWindow() {
	delete priv;
	for (auto p : priv->mp_proxy_list) delete p;
}

MyArea* MainWindow::getMyArea() {
	return priv->mp_area;
}

void MainWindow::gtkActionRunCode(const char* name, const char* code) {
	priv->map_action2data(name, code, true);
}

void MainWindow::gtkActionRunAction(const char* name, const char* action) {
	priv->map_action2data(name, action, false);
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

MainWindow_private::MainWindow_private(const Glib::RefPtr<Gtk::Builder>& builder) 
	: m_builder(builder)
{

}

MainWindow_private::~MainWindow_private() {

}

void MainWindow_private::map_action2data(const char* name, const char* data, bool is_code) {
	Glib::RefPtr<Gtk::Action> pAction = Glib::RefPtr<Gtk::Action>::cast_dynamic(
		m_builder->get_object(name));
	if (!pAction) return;
	ActionProxy* pProxy = new ActionProxy(data, is_code);
	pAction->signal_activate().connect(
		sigc::mem_fun(*pProxy, &ActionProxy::Activate) );

	mp_action_list.push_back(pAction);
	mp_proxy_list.push_back(pProxy);
}
