/* 
* @Author: sxf
* @Date:   2015-05-29 11:28:22
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 20:35:42
*/

#ifndef MSG_H
#define MSG_H

#include <string>

/**
 * @brief 这个结构体将被luacontainer内部使用，用作异步执行代码的消息之用，不应提供给其他人使用该类
 */
struct msg
{
	int type;
	std::string data;

	msg(int _type, const char* _data) {
		type = _type;
		data = _data;
	}
	~msg() {}

	msg(const msg& _msg) {
		type = _msg.type;
		data = _msg.data;
	}
	msg& operator=(const msg& _msg) {
		type = _msg.type;
		data = _msg.data;
		return *this;
	}
};

#endif // MSG_H
