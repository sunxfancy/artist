/* 
* @Author: sxf
* @Date:   2015-06-02 14:10:32
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 20:37:40
*/
#ifndef BRUSH_H
#define BRUSH_H

#include "tools/tool.h"

typedef sigc::signal<void, double, double, int> t_brush_move_hook;
typedef sigc::signal<void> t_brush_notice_hook;

class Brush_private;
class Brush : public Tool
{
public:
	Brush();
	virtual ~Brush();

	t_brush_notice_hook signal_brush_begin();
	t_brush_notice_hook signal_brush_end();
	t_brush_move_hook signal_brush_move();
protected:
	Brush_private* priv;
};


#endif // BRUSH_H
