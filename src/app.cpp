/* 
* @Author: sxf
* @Date:   2015-05-29 19:09:27
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-31 15:49:51
*/

#include "app.h"

class App_private
{
public:
	MainWindow* 	mainWindow;
	LuaContainer*	luaContainer;
	ActionManager*	actionManager;
	PackageManager* packageManager;

	void init();
};

App::App() {
	priv = new App_private();
}

void App::Init() {
	App& app = getInstance();
	app.priv->init();
}

MainWindow* App::getMainWindow() {
	return getInstance().priv->mainWindow;
}

LuaContainer* App::getLuaContainer() {
	return getInstance().priv->luaContainer;
}

ActionManager* App::getActionManager() {
	return getInstance().priv->actionManager;
}

PackageManager* App::getPackageManager() {
	return getInstance().priv->packageManager;
}

App& App::getInstance()  
{  
    static App instance;   //局部静态变量  
    return instance;  
}

void App_private::init() {
	mainWindow     = MainWindow::CreateFromBuilder();
	luaContainer   = new LuaContainer();
	packageManager = new PackageManager();
	actionManager  = new ActionManager();

	luaContainer->RunLuaShell();
	luaContainer->RunLuafile("packages/init.lua");
}