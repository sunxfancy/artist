/* 
* @Author: sxf
* @Date:   2015-05-29 18:47:41
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-08 17:12:22
*/

#ifndef APP_H
#define APP_H

#include "ui/mainwindow.h"
#include "packages/luacontainer.h"
#include "packages/actionmanager.h"
#include "packages/packagemanager.h"
#include "packages/package.h"
#include "ui/myarea.h"
#include "tools/tools.h"
#include "pixels/bitmap.h"

class App_private;
class App
{
private:
	App();
	App_private* priv;

public:
	static void Init();  
	static MyArea* 			getMyArea();
	static MainWindow* 		getMainWindow();
	static Tools*			getTools();
	static LuaContainer* 	getLuaContainer();
	static ActionManager* 	getActionManager();
	static PackageManager*  getPackageManager();
	static Bitmap*			getBitmap();
	static App& getInstance();
};


#endif // APP_H
