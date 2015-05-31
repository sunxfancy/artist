/* 
* @Author: sxf
* @Date:   2015-05-29 18:47:41
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-31 15:28:48
*/

#ifndef APP_H
#define APP_H

#include "mainwindow.h"
#include "luacontainer.h"
#include "actionmanager.h"
#include "packagemanager.h"

class App_private;
class App
{
private:
	App();
	App_private* priv;

public:
	static void Init();  
	static MainWindow* 		getMainWindow();
	static LuaContainer* 	getLuaContainer();
	static ActionManager* 	getActionManager();
	static PackageManager*  getPackageManager();
	static App& getInstance();
};


#endif // APP_H
