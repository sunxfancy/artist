/* 
* @Author: sxf
* @Date:   2015-06-01 21:20:51
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 21:24:03
*/

#ifndef FILELOADER_H
#define FILELOADER_H

class FileLoader
{
public:
	/**
	 * @brief 加载一个文件到字符串，使用完后注意释放内存，delete掉
	 * @param path 文件的路径
	 */
	static char* load(const char* path);
};

#endif // FILELOADER_H

