/* 
* @Author: sxf
* @Date:   2015-06-03 22:56:32
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-08 16:56:09
*/

#ifndef BITMAP_H
#define BITMAP_H

#include <gtkmm.h>

class Bitmap_private;
class Bitmap
{
public:
	Bitmap();
	~Bitmap();

	Gdk::Pixbuf* getData();
	void draw_circle(double x, double y, double r, 
		unsigned int color = 0x000000ff, double yh = 2.0f);

protected:
	Bitmap_private* priv;
};

#endif // BITMAP_H
