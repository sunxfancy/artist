/* 
* @Author: sxf
* @Date:   2015-05-07 12:22:40
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-29 19:32:29
*/

#include <gtkmm.h>
#include "app.h"

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.abs.artist");

	// 初始化应用
	App::Init();

	MainWindow* mainWindow = App::getMainWindow();

	//Shows the window and returns when it is closed.
	if (mainWindow)
		return app->run(*mainWindow);
	return 1;
}