/* 
* @Author: sxf
* @Date:   2015-06-02 14:17:26
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-02 20:35:26
*/

#include "tools/brush.h"

class Brush_private
{
public:
	bool mouse_click(double x, double y);
	bool mouse_release(double x, double y);
	bool mouse_move(double x, double y);	

	t_brush_notice_hook brush_begin;
	t_brush_notice_hook brush_end;
	t_brush_move_hook brush_move;

	int default_pressure;
};

Brush::Brush()
	: Tool("brush") 
{
	priv = new Brush_private();
	priv->default_pressure = 1000;
	signal_mouse_click().connect(
		sigc::mem_fun(*priv, &Brush_private::mouse_click));
	signal_mouse_move().connect(
		sigc::mem_fun(*priv, &Brush_private::mouse_move));
	signal_mouse_release().connect(
		sigc::mem_fun(*priv, &Brush_private::mouse_release));
}

Brush::~Brush() {
	delete priv;
}

t_brush_notice_hook Brush::signal_brush_begin() {
	return priv->brush_begin;
}

t_brush_notice_hook Brush::signal_brush_end() {
	return priv->brush_end;
}

t_brush_move_hook Brush::signal_brush_move() {
	return priv->brush_move;
}


bool Brush_private::mouse_click(double x, double y) {
	brush_begin.emit();
	brush_move.emit(x, y, default_pressure);
	return false;
}

bool Brush_private::mouse_release(double x, double y) {
	brush_move.emit(x, y, default_pressure);
	brush_end.emit();
	return false;
}

bool Brush_private::mouse_move(double x, double y) {
	brush_move.emit(x, y, default_pressure);
	return false;
}
