/* 
* @Author: sxf
* @Date:   2015-05-29 19:09:27
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 17:02:35
*/

#include "app.h"
#include "tools/luatool.h"

class App_private
{
public:
	MainWindow* 	mainWindow;
	MyArea*			myArea;
	LuaContainer*	luaContainer;
	ActionManager*	actionManager;
	PackageManager* packageManager;
	Tools* 			tools;
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

MyArea* App::getMyArea() {
	return getInstance().priv->myArea;
}

Tools* App::getTools() {
	return getInstance().priv->tools;
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
	myArea         = mainWindow->getMyArea();
	tools          = new Tools();

	ActionManager::signal_run_lua_code.connect(
		sigc::mem_fun(*luaContainer, &LuaContainer::RunLuaCode));
	Package::signal_run_lua_file.connect(
		sigc::mem_fun(*luaContainer, &LuaContainer::RunLuaFile));
	Package::signal_action_register.connect(
		sigc::mem_fun(*actionManager, &ActionManager::Register));
	LuaTool::signal_run_task.connect(
		sigc::mem_fun(*luaContainer, &LuaContainer::RunTask));

	luaContainer->RunLuaShell();
	luaContainer->RunLuaFile("packages/init.lua");
}