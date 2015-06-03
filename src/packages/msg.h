/* 
* @Author: sxf
* @Date:   2015-05-29 11:28:22
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 16:21:35
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
	void* cfunc;
	void* args;

	msg(int _type, const char* _data) {
		type = _type;
		data = _data;
	}
	msg(int _type, void* _cfunc, void* _args) {
		type = _type;
		cfunc = _cfunc;
		args  = _args;
	}
	~msg() {}

	msg(const msg& _msg) {
		type  = _msg.type;
		data  = _msg.data;
		cfunc = _msg.cfunc;
		args  = _msg.args;
	}
	msg& operator=(const msg& _msg) {
		type  = _msg.type;
		data  = _msg.data;
		cfunc = _msg.cfunc;
		args  = _msg.args;
		return *this;
	}
};

#endif // MSG_H
