/* 
* @Author: sxf
* @Date:   2015-05-30 12:28:33
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-31 15:24:02
*/

#ifndef PackageManager_H
#define PackageManager_H

class PackageManager_private;
class PackageManager
{
public:
	PackageManager();
	~PackageManager();

	void LoadPackage(const char* path);
	void Search();
	void addSearchPath(const char* path);
	void removeAllPath();
protected:
	PackageManager_private* priv;
};

#endif // PackageManager_H
