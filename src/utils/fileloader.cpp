/* 
* @Author: sxf
* @Date:   2015-06-01 21:21:39
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 21:24:21
*/

#include "fileloader.h"
#include <fstream>

char* FileLoader::load(const char* path) {
	std::fstream file;
	file.open(path);//打开文件
    if(!file.is_open()) {
        printf("can not open json file!\n");
        return NULL;
    }
    file.seekg(0,std::ios::end);
    int flen = file.tellg();
    file.seekg(0,std::ios::beg);
    char* data = new char[flen+1];
    file.read(data,flen);
    file.close();
    data[flen] = 0;
    return data;
}