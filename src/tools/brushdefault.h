/* 
* @Author: sxf
* @Date:   2015-06-08 15:17:53
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-08 16:11:23
*/
#ifndef BRUSHDEFAULT_H
#define BRUSHDEFAULT_H

#include "tools/tool.h"

class BrushDefault_private;
class BrushDefault : public Tool {
public:
	BrushDefault();
	virtual ~BrushDefault();

protected:
	BrushDefault_private* priv;
};

#endif // BRUSHDEFAULT_H
