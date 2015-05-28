/* 
* @Author: sxf
* @Date:   2015-05-07 12:22:40
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-28 21:02:24
*/

#include <gtkmm.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.abs.artist");

	MainWindow* mainWindow = MainWindow::CreateFromBuilder();

	//Shows the window and returns when it is closed.
	if (mainWindow)
		return app->run(*mainWindow);

	sleep(1);
	return 1;
}