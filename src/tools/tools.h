/* 
* @Author: sxf
* @Date:   2015-06-01 14:02:32
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-01 14:04:26
*/
#ifndef TOOLS_H
#define TOOLS_H

class Tools_private;
class Tools
{
public:
	Tools();
	~Tools();

	void AddToolFromJson(const char* json_path);
	void AddTool();
protected:
	Tools_private* priv;
};


#endif // TOOLS_H
