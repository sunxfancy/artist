/* 
* @Author: sxf
* @Date:   2015-09-01 13:27:06
* @Last Modified by:   sxf
* @Last Modified time: 2015-09-02 13:21:33
*/

#include "brushbezier.h"
#include <math.h>
#include "app.h"
#include <deque>

using namespace std;

typedef struct _point2d
{
	double x, y;
} point2d;


class BrushBezier_private
{
public:
	BrushBezier_private();
	~BrushBezier_private();
	
	BrushBezier* publ;

	double r = 5.0;
	double jg = 2.0;

	point2d v, b;
	point2d last, lastt;
	point2d lastm, lasttm;
	Bitmap* bitmap;

	int mbs = 10;
	double fz = 1.0;
	deque<point2d> points_queue;
	deque<int> smooth_points_set;
	bool mouse_click(double, double);
	bool mouse_release(double, double);
	bool mouse_move(double, double);

	void line(point2d p1, point2d p2);
	void smooth(int i, int j);

	void draw_arc(double x, double y);
	void draw_ph_arc(double x, double y);
	void draw_bezier(point2d p0, point2d p1, point2d p2, point2d p3, int n);
	void draw_line(double x, double y);
};

BrushBezier::BrushBezier()
	: Tool("brush-bezier") {
	priv = new BrushBezier_private();
	priv->publ = this;
	signal_mouse_click().connect(
		sigc::mem_fun(*priv, &BrushBezier_private::mouse_click));
	signal_mouse_move().connect(
		sigc::mem_fun(*priv, &BrushBezier_private::mouse_move));
	signal_mouse_release().connect(
		sigc::mem_fun(*priv, &BrushBezier_private::mouse_release));
}

BrushBezier::~BrushBezier() {
	delete priv;
}

BrushBezier_private::BrushBezier_private() {
	
}

BrushBezier_private::~BrushBezier_private() {
	
}

bool BrushBezier_private::mouse_click(double x, double y) {
	bitmap = App::getBitmap();
	MyArea* area = App::getMyArea();
	v.x = 0; v.y = 0;
	last = {.x = x, .y = y};
	lastt = lasttm = lastm = b = last;
	bitmap->draw_circle(x, y, r, 0x111111ff, 4.0);
	printf("%f %f\n", x, y);
	area->update();
	return false;
}

bool BrushBezier_private::mouse_release(double x, double y) {
	printf("%s\n", "mouse_release");
	points_queue.clear();
	smooth_points_set.clear();
	return false;
}


void BrushBezier_private::draw_line(double x, double y) {
	double ax = x - b.x;
	double ay = y - b.y;
	double d = sqrt(ax*ax + ay*ay);
	bitmap->draw_circle(x, y, r, 0x111111ff, 4.0);
	if (d < jg) return;
	int n = floor(d / jg);
	for (int i = 1; i<= n; ++i) {
		b.x = last.x + i * (ax / n);
		b.y = last.y + i * (ay / n);
		bitmap->draw_circle(b.x, b.y, r, 0x111111ff, 4.0);
	}
}

void BrushBezier_private::line(point2d p1, point2d p2) {
	double ax = p2.x - p1.x;
	double ay = p2.y - p1.y;
	double d = sqrt(ax*ax + ay*ay);
	double x, y;
	bitmap->draw_circle(p1.x, p1.y, r, 0x111111ff, 4.0);
	if (d < jg) return;
	int n = floor(d / jg);
	for (int i = 0; i< n; ++i) {
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

void BrushBezier_private::draw_bezier(point2d p0, point2d p1, point2d p2, point2d p3, int n) {
	point2d ans;
	bitmap->draw_circle(p0.x, p0.y, r, 0x111111ff, 4.0);
	for (int i = 0; i <= n; ++i) {
		double t = (double)i / (double)n;
		ans.x = p0.x * pow(1-t, 3) + 3 * p1.x * t * pow(1-t, 2) +
				3 * p2.x * t*t * (1-t) + p3.x * pow(t,3);
		ans.y = p0.y * pow(1-t, 3) + 3 * p1.y * t * pow(1-t, 2) + 
				3 * p2.y * t*t * (1-t) + p3.y * pow(t,3);
		bitmap->draw_circle(ans.x, ans.y, r, 0x111111ff, 4.0);
	}
}

void BrushBezier_private::draw_arc(double x, double y) {
	double ax = x - b.x;
	double ay = y - b.y;
	double d = sqrt(ax*ax + ay*ay);
	point2d now = {x,y};
	point2d nowmid = midpoint(last, now);

	point2d p1 = midpoint(lastm, lasttm);
	point2d p2 = midpoint(nowmid, lastm);

	point2d pc1 = {lastm.x + lastt.x - p1.x, lastm.y + lastt.y - p1.y};
	point2d pc2 = {lastm.x + last.x - p2.x, lastm.y + last.y - p2.y};

	draw_bezier(lastt, pc1, pc2, last, floor(d/jg));

	lasttm = lastm;
	lastm = nowmid;
	lastt = last;
}

void BrushBezier_private::smooth(int i, int j) {
	double maxl = 0; int maxn = -1;
	for (int p = i+1; p < j; ++p) {
		double l = distance(points_queue[i], 
							points_queue[j], points_queue[p]);
		if (l > maxl) { 
			maxl = l; maxn = p;
		}
	}
	if (maxl < fz) {
		smooth_points_set.push_back(i);
	} else {
		smooth(i, maxn);
		smooth(maxn, j);
	}
}


void BrushBezier_private::draw_ph_arc(double x, double y) {
	point2d end = {x, y};
	points_queue.push_back(end);
	if (points_queue.size() >= mbs) {
		smooth_points_set.clear();
		smooth(0, points_queue.size()-1);
		smooth_points_set.push_back(points_queue.size()-1);

		point2d llast = points_queue[smooth_points_set[0]];
		point2d lnew = points_queue[smooth_points_set[1]];
		double x = lnew.x - llast.x;
		double y = lnew.y - llast.y;
		point2d last_b = b;
		b.x += x / (mbs-1);
		b.y += y / (mbs-1);
		line(last_b, b);
		llast = lnew;
		points_queue.pop_front();
		points_queue.pop_front();
		points_queue.push_front(b);
	}
}

bool BrushBezier_private::mouse_move(double x, double y) {
	bitmap = App::getBitmap();
	MyArea* area = App::getMyArea();
	int time = publ->getDeltaTime();
	
	draw_ph_arc(x, y);
	
	last.x = x; last.y = y;
	area->update();
	return false;
}


