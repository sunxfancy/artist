/* 
* @Author: sxf
* @Date:   2015-06-03 22:57:44
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-08 22:31:23
*/

#include "bitmap.h"

class Bitmap_private
{
public:
	Bitmap_private();
	~Bitmap_private();

	void draw_circle(double x, double y, double r, unsigned int color, double yh);
	unsigned char draw_pixel(unsigned char channel_new, unsigned char channel_old, unsigned char yh);

	double b = 0.25;

	Glib::RefPtr< Gdk::Pixbuf > pixbuf;
};

Bitmap::Bitmap() {
	priv = new Bitmap_private();
	double x = 150, y = 150, r = 50;
	draw_circle(x, y, r, 0x000000ff, 30.0);
	draw_circle(x + 60, y, r, 0x000000ff, 30.0);
	// draw_circle(x + 20, y, r, 0x000000ff, 1.0);
}

Bitmap::~Bitmap() {
	delete priv;
}

Gdk::Pixbuf* Bitmap::getData() {
	return priv->pixbuf.operator->();
}

void Bitmap::draw_circle(double x, double y, double r, unsigned int color, double yh) {
	priv->draw_circle(x, y, r, color, yh);
}

Bitmap_private::Bitmap_private() {
	pixbuf = Gdk::Pixbuf::create(Gdk::Colorspace::COLORSPACE_RGB, true, 8, 800, 640);
	pixbuf->fill(0xffffffff);
}

Bitmap_private::~Bitmap_private() {
	
}

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define xz(x, x_min, x_max) (min( max(x, x_min) , x_max))

unsigned char Bitmap_private::draw_pixel(unsigned char channel_new, 
	unsigned char channel_old, unsigned char yh) {
	double d = (double)yh / (double)255;
	int ans = 0xff - floor((0xff - channel_old) * (1-d)
		+ (0xff - channel_new) * d );
	ans = xz(ans, 0, 0xff);
	return ans;
}

void Bitmap_private::draw_circle(double x, double y, double r, unsigned int color, double yh) {
	guint8* data = pixbuf->get_pixels();
	int w = pixbuf->get_width();
	int h = pixbuf->get_height();

	#define pixel_r(px, py) data[( px * w + py )*4]
	#define pixel_g(px, py) data[( px * w + py )*4 + 1]
	#define pixel_b(px, py) data[( px * w + py )*4 + 2]
	#define pixel_a(px, py) data[( px * w + py )*4 + 3]

	double c = 20.0;
	int vb = ceil(y - r); int ve = floor(y + r);
	vb = max(0, vb); ve = min(ve, h);
	for (int i = vb; i <= ve; ++i) {
		double xm = sqrt( r*r - pow(y - i - 0.5, 2) );
		int hb = ceil(x - xm); int he = floor(x + xm);
		hb = max(0, hb); he = min(he, w);
		for (int j = hb; j < he; ++j) {
			// 高斯函数
			// int f = floor( 255.0 * exp( -(pow(y - i - 0.5, 2) + pow(x - j - 0.5, 2)) / (c*c) ) );
			double d = sqrt(pow(y - i - 0.5, 2) + pow(x - j - 0.5, 2));
			int ff = floor((r - d)*255/yh);
			ff = xz(ff, 0, 255);
			unsigned char f = (r - d) < yh ? ff : 0xff;
			pixel_r(i,j) = draw_pixel((color >> 24) & 0xff, pixel_r(i,j), f);
			pixel_g(i,j) = draw_pixel((color >> 16) & 0xff, pixel_g(i,j), f);
			pixel_b(i,j) = draw_pixel((color >> 8 ) & 0xff, pixel_b(i,j), f);
			pixel_a(i,j) = (unsigned char) (color & 0xff);
		}
	}
}