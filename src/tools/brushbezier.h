/* 
* @Author: sxf
* @Date:   2015-09-01 13:24:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-09-01 13:28:32
*/

#ifndef BRUSHBEZIER_H
#define BRUSHBEZIER_H

#include "tools/tool.h"

class BrushBezier_private;
class BrushBezier : public Tool {
public:
	BrushBezier();
	virtual ~BrushBezier();
protected:
	BrushBezier_private* priv;
};

#endif // BRUSHBEZIER_H
