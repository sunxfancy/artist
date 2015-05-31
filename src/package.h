/* 
* @Author: sxf
* @Date:   2015-05-30 13:20:33
* @Last Modified by:   sxf
* @Last Modified time: 2015-05-30 18:47:42
*/

#ifndef PACKAGE_H
#define PACKAGE_H

class Package_private;
class Package
{
public:
	Package(const char* json_path);
	~Package();

	void Load();
	void UnLoad();
	const char* getName() const;
protected:
	Package_private* priv;
};


#endif // PACKAGE_H
