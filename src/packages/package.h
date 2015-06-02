/* 
* @Author: sxf
* @Date:   2015-05-30 13:20:33
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 20:39:08
*/

#ifndef PACKAGE_H
#define PACKAGE_H

class Package_private;

/**
 * @brief 这个类是一个插件包的实例类，负责包的加载或卸载
 */
class Package
{
public:
	/**
	 * @brief 构造函数，从一个json文件的路径构造一个包，传入的应该是一个meta文件
	 * @param json_path json文件的路径
	 */
	Package(const char* json_path); 
	~Package();

	/**
	 * @brief 加载一个包
	 */
	void Load();

	/**
	 * @brief 卸载这个包
	 */
	void UnLoad();

	/**
	 * @brief 获取包的名字，一个包的名字默认在meta文件中的name字段定义，如果没有该字段，则以包文件夹的名字为包名
	 */
	const char* getName() const;
protected:
	Package_private* priv;
};


#endif // PACKAGE_H
