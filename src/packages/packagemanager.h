/* 
* @Author: sxf
* @Date:   2015-05-30 12:28:33
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 20:43:48
*/

#ifndef PackageManager_H
#define PackageManager_H

class PackageManager_private;

/**
 * @brief 包管理器类，负责包的搜索与路径计算
 */
class PackageManager
{
public:
	PackageManager();
	~PackageManager();

	/**
	 * @brief 加载指定位置的一个包，请确保这个路径是一个meta文件
	 * @param path 该包下meta文件的路径
	 */
	void LoadPackage(const char* path);

	/**
	 * @brief 从一个路径以以下规则递归搜索，如果判断存在meta文件，则认为是一个包，停止搜索，否则继续搜索其中的文件夹
	 */
	void Search();

	/**
	 * @brief 添加一个搜索路径
	 * @param path 要添加的路径
	 */
	void addSearchPath(const char* path);

	/**
	 * @brief 移除所有搜索路径
	 */
	void removeAllPath();
protected:
	PackageManager_private* priv;
};

#endif // PackageManager_H
