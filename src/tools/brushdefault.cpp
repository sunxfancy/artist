/* 
* @Author: sxf
* @Date:   2015-06-08 15:19:40
* @Last Modified by:   sxf
* @Last Modified time: 2015-09-01 14:44:09
*/

#include "brushdefault.h"
#include <math.h>
#include "app.h"
#include <deque>

using namespace std;

typedef struct _point2d
{
	double x, y;
} point2d;

class BrushDefault_private
{
public:
	BrushDefault_private();
	~BrushDefault_private();

	BrushDefault* publ;

	double r = 5.0;
	double jg = 2.0;

	Bitmap* bitmap;

	int mbs = 10;
	double fz = 1.0;
	deque<point2d> points_queue;
	bool mouse_click(double, double);
	bool mouse_release(double, double);
	bool mouse_move(double, double);

	void line(point2d p1, point2d p2);
	int smooth(int i, int j);

	void draw_line(double x, double y);
};

BrushDefault::BrushDefault() 
	: Tool("brush-default")
{
	priv = new BrushDefault_private();
	priv->publ = this;
	signal_mouse_click().connect(
		sigc::mem_fun(*priv, &BrushDefault_private::mouse_click));
	signal_mouse_move().connect(
		sigc::mem_fun(*priv, &BrushDefault_private::mouse_move));
	signal_mouse_release().connect(
		sigc::mem_fun(*priv, &BrushDefault_private::mouse_release));
}

BrushDefault::~BrushDefault() {
	delete priv;
}

BrushDefault_private::BrushDefault_private() {
	
}

BrushDefault_private::~BrushDefault_private() {
	
}

bool BrushDefault_private::mouse_click(double x, double y) {
	bitmap = App::getBitmap();
	MyArea* area = App::getMyArea();
	point2d p = {.x = x, .y = y};
	points_queue.push_back(p);
	bitmap->draw_circle(x, y, r, 0x111111ff, 4.0);
	printf("%f %f\n", x, y);
	area->update();
	return false;
}

bool BrushDefault_private::mouse_release(double x, double y) {
	points_queue.clear();
	return false;
}

void BrushDefault_private::line(point2d p1, point2d p2) {
	double ax = p2.x - p1.x;
	double ay = p2.y - p1.y;
	double d = sqrt(ax*ax + ay*ay);
	double x, y;
	bitmap->draw_circle(p1.x, p1.y, r, 0x111111ff, 4.0);
	if (d < jg) return;
	int n = floor(d / jg);
	for (int i = 1; i<= n; ++i) {
		x = p1.x + i * ax / n;
		y = p1.y + i * ay / n;
		bitmap->draw_circle(x, y, r, 0x111111ff, 4.0);
	}
}


inline point2d midpoint(point2d p1, point2d p2) {
	point2d ans = { (p1.x + p2.x) /2, (p1.y + p2.y) /2 };
	return ans;
}

inline double length(point2d p1, point2d p2) {
	double ax = p1.x - p2.x;
	double ay = p1.y - p2.y;
	return sqrt(ax*ax + ay*ay);
}

inline double distance(point2d pbegin, point2d pend, point2d pobj) {
	double a = length(pbegin, pobj);
	double b = length(pend, pobj);
	double c = length(pbegin, pend);
	double l = (a+b+c)/2;     //周长的一半  
	double s = sqrt(l*(l-a)*(l-b)*(l-c));  //海伦公式求面积  
	return 2*s/c;
}

inline point2d getNewPoint(point2d src, point2d obj, int k) {
	point2d ans = { src.x + (obj.x - src.x) /k, src.y + (obj.y - src.y) /k };
	return ans;
}


int BrushDefault_private::smooth(int i, int j) {
	double maxl = 0; int maxn = -1;
	for (int p = i+1; p < j; ++p) {
		double l = distance(points_queue[i], 
							points_queue[j], points_queue[p]);
		if (l > maxl) { 
			maxl = l; maxn = p;
		}
	}
	if (maxl < fz) {
		// smooth_points_set.push_back(i);
		return j;
	} else {
		return smooth(i, maxn);
		// smooth(maxn, j); 由于我们要找最靠前的可行位置点，于是不用找另一半了
	}
}

bool BrushDefault_private::mouse_move(double x, double y) {
	bitmap = App::getBitmap();
	MyArea* area = App::getMyArea();
	int time = publ->getDeltaTime();
	point2d p = {.x = x, .y = y};
	points_queue.push_back(p);
	if (points_queue.size() > mbs) {
		int k = smooth(0, points_queue.size()-1);
		point2d bp = points_queue[0];
		point2d np = getNewPoint(bp, points_queue[k], k);
		points_queue.pop_front();
		points_queue.pop_front();
		points_queue.push_front(np);
		line(bp, np);
		printf("bp: %f %f\n", bp.x, bp.y);
		printf("np: %f %f\n", np.x, np.y);
	}
	area->update();
	return false;
}


