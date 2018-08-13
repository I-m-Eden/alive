#pragma once
#include "head.h"
#include "winpaint.h"
using namespace std;
const int IDTREE = 1;
const int IDTREE2 = 9;
const int IDSTONE = 2;
const int IDFRUIT = 5;
const int IDENEMY1 = 3;
const int IDENEMY2 = 4;
const int IDENEMY3 = 6;
const int IDENEMY4 = 7;
const int IDBOSS1 = 8;
class figureimage {
private:
	void drawellipse(COLORREF fc, double x1, double y1, double x2, double y2, int d) {
		int varX = (int)round( (sqrt(d*d - (y2 - y1)*(y2 - y1)) - fabs(x2 - x1) / 2) );
		int XL = (int)round(min(x1, x2)) - varX, XR = (int)round(max(x1, x2)) + varX;
		int varY = (int)round( (sqrt(d*d - (x2 - x1)*(x2 - x1)) - fabs(y2 - y1) / 2) );
		int YL = (int)round(min(y1, y2)) - varY, YR = (int)round(max(y1, y2)) + varY;
		for (int X = XL; X <= XR; ++X)for (int Y = YL; Y <= YR; ++Y) {
			int dd = (int)round(sqrt((X - x1)*(X - x1) + (Y - y1)*(Y - y1)) + sqrt((X - x2)*(X - x2) + (Y - y2)*(Y - y2)));
			if (dd <= d)pdot(X, Y, fc);
		}
	}
	double px, py;
	int x1, y1; 
	int x21, y21, x22, y22, d2; 
	int x31, y31, x32, y32, d3;
public:
	COLORREF fc1,fc2,fc3;
	int r1;
	double angle;
	figureimage() { 
		x1 = y1 = 0; r1 = 40; fc1 = RGB(10, 10, 10);
		x21 = -20; y21 = 2; x22 = -15; y22 = -13; d2 = 22; fc2 = RGB(20, 20, 20);
		x31 = -7; y31 = -39; x32 = 7; y32 = -37; d3 = 17; fc3 = RGB(20, 20, 20);
		angle = 0;
		px = 0; py = 0;
	}
	void setposition(double x, double y) { px = x; py = y; }
	void setposition(vector2 p) { setposition(p.x, p.y); }
	vector2 getposition() { return vector2(px, py); }
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		int X1 = (int)round(ca*x1 - sa * y1), Y1 = (int)round(sa*x1 + ca * y1);
		setf(fc1);
		fcircle((int)round(px + X1), (int)round(py + Y1), r1);
		double X21 = ca*x21 - sa * y21, Y21 = sa*x21 + ca * y21;
		double X22 = ca*x22 - sa * y22, Y22 = sa*x22 + ca * y22;
		drawellipse(fc2, X21 + px, Y21 + py, X22 + px, Y22 + py, d2);
		X21 = -ca * x21 - sa * y21, Y21 = -sa * x21 + ca * y21;
		X22 = -ca * x22 - sa * y22, Y22 = -sa * x22 + ca * y22;
		drawellipse(fc2, X21 + px, Y21 + py, X22 + px, Y22 + py, d2);
		double X31 = ca*x31 - sa * y31, Y31 = sa*x31 + ca * y31;
		double X32 = ca*x32 - sa * y32, Y32 = sa*x32 + ca * y32;
		drawellipse(fc3, X31 + px, Y31 + py, X32 + px, Y32 + py, d3);
	}
}figuredemo;
class treeimage {
private:
	int ps, pw;COLORREF pc;
	double x, y;
public:
	COLORREF fc;
	double r;
	treeimage() {
		ps = 0; pw = 0; pc = BLACK;
		fc = 0x85DA2F;
		r = 50;
		x = y = 0;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		setd(ps, pw, pc);
		setf(fc);
		pcircle((int)round(x), (int)round(y), (int)round(r));
	}
}treedemo;
class tree2image {
private:
	int ps, pw; COLORREF pc;
	double x, y;
public:
	COLORREF fc;
	double r;
	tree2image() {
		ps = 0; pw = 0; pc = BLACK;
		fc = RGB(100,200,0);
		r = 54;
		x = y = 0;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		setd(ps, pw, pc);
		setf(fc);
		pcircle((int)round(x), (int)round(y), (int)round(r));
	}
}tree2demo;
class stoneimage {
private:
	int ps, pw; COLORREF pc;
	double x, y;
public:
	COLORREF fc;
	int r;
	stoneimage() {
		ps = 0; pw = 0; pc = BLACK;
		fc = 0xA9A9AC;
		r = 30;
		x = y = 0;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		setd(ps, pw, pc);
		setf(fc);
		pcircle((int)round(x), (int)round(y), r);
	}
}stonedemo;
class fruitimage {
private:
	int ps, pw; COLORREF pc, spc;
	double x, y;
public:
	COLORREF fc, sfc;
	double r, sr;
	fruitimage() {
		ps = 0; pw = 0; pc = RGB(250, 210, 70); spc = RGB(250, 250, 100);
		fc = RGB(200, 160, 20); sfc = RGB(200, 230, 50);
		r = 12; sr = 6;
		x = y = 0;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		setd(ps, pw, pc);
		setf(fc);
		pcircle((int)round(x), (int)round(y), (int)round(r));
		setd(ps, pw, spc);
		setf(sfc);
		pcircle((int)round(x), (int)round(y), (int)round(sr));
	}
}fruitdemo;
class enemyimage {
private:
	POINT S[50];
	int ps1, pw1; COLORREF pc1;
	int ps2, pw2; COLORREF pc2;
	double x, y;
	double sz;
	int Sn = 50; POINT s[50] = {
	{ 0,65 },
	{ -11,64 },
	{ -17,62 },
	{ -22,60 },
	{ -25,58 },
	{ -32,51 },
	{ -35,47 },
	{ -38,42 },
	{ -40,37 },
	{ -42,30 },
	{ -43,27 },
	{ -44,22 },
	{ -45,17 },
	{ -46,11 },
	{ -46,1 },
	{ -45,-5 },
	{ -44,-11 },
	{ -43,-16 },
	{ -42,-20 },
	{ -38,-28 },
	{ -32,-38 },
	{ -22,-52 },
	{ -13,-61 },
	{ -8,-63 },
	{ -5,-64 },
	{ 0,-65 }
	};
	int Tn = 19; POINT t[19] = {
	{ -40,-3 },
	{ -40,-10 },
	{ -38,-18 },
	{ -36,-22 },
	{ -34,-25 },
	{ -31,-29 },
	{ -25,-34 },
	{ -21,-36 },
	{ -16,-38 },
	{ -13,-39 },
	{ -4,-39 },
	{ -5,-34 },
	{ -8,-25 },
	{ -11,-19 },
	{ -21,-9 },
	{ -24,-8 },
	{ -27,-6 },
	{ -29,-5 },
	{ -33,-4 }
	};
public:
	COLORREF fc1, fc2;
	double angle;
	double rw, rh, r;
	enemyimage(double sz) {
		rw = 42.0; rh = 65.0; r = min(rw, rh);
		ps1 = 0; pw1 = 0; pc1 = 0x788870;
		fc1 = 0xA0B0A0;
		ps2 = 0; pw2 = 0; pc2 = 0xB2EB79;
		fc2 = 0x8FCF4F;
		angle = 0; setsize(sz);
		x = y = 0;
		for (int i = Sn/2+1; i < Sn; ++i)
			s[i] = s[Sn - i], s[i].x = -s[i].x;
	}
	void setsize(double Sz) {
		sz = Sz; rw = rw * sz; rh = rh * sz; r = r * sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		for (int i = 0; i < Sn; ++i)S[i] = s[i];
		for (int i = 0; i < Sn; ++i)S[i] = { (int)round(sz*(S[i].x*ca - S[i].y*sa) + x),(int)round(sz*(S[i].x*sa + S[i].y*ca) + y) };
		setd(ps1, pw1, pc1);
		setf(fc1);
		ppolygon(S, Sn);
		for (int i = 0; i < Tn; ++i)S[i] = t[i];
		for (int i = 0; i < Tn; ++i)S[i] = { (int)round(sz*(S[i].x*ca - S[i].y*sa) + x),(int)round(sz*(S[i].x*sa + S[i].y*ca) + y) };
		setd(ps1, pw1, pc1);
		setf(fc2);
		ppolygon(S, Tn);
		for (int i = 0; i < Tn; ++i)S[i] = t[i], S[i].x = -S[i].x;
		for (int i = 0; i < Tn; ++i)S[i] = { (int)round(sz*(S[i].x*ca - S[i].y*sa) + x),(int)round(sz*(S[i].x*sa + S[i].y*ca) + y) };
		setd(ps1, pw1, pc1);
		setf(fc2);
		ppolygon(S, Tn);
	}
}enemy1demo(0.5), enemy3demo(0.2);
class bulletimage {
private:
	double x, y;
public:
	COLORREF fc;
	double r;
	bulletimage() {
		fc = BLACK;
		r = 5;
		x = y = 0;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		setf(fc);
		fcircle((int)round(x), (int)round(y), (int)round(r));
	}
}bulletdemo;
class enemy2image {
private:
	int Sn; POINT S[10];
	int ps1, pw1; COLORREF pc1;
	int ps2, pw2; COLORREF pc2;
	double x, y;
	double sz;
	POINT s[4] = {
		{-30,35},
		{0,-30},
		{30,35},
		{0,15}
	};
	POINT t[3] = {
		{-18,15},
		{-3,-10},
		{-3,5}
	};
public:
	COLORREF fc1, fc2;
	double angle;
	double rw, rh, r;
	enemy2image() {
		rw = 30.0; rh = 35.0; r = min(rw, rh);
		ps1 = 0; pw1 = 0; pc1 = 0x788870;
		fc1 = rgb(237, 220, 12);
		ps2 = 0; pw2 = 0; pc2 = 0xB2EB79;
		fc2 = rgb(240, 187, 77);
		angle = 0; setsize(0.5);
		x = y = 0;
	}
	void setsize(double Sz) {
		sz = Sz; rw = rw * sz; rh = rh * sz; r = r * sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		for (int i = 0; i < 4; ++i)S[i] = s[i];
		for (int i = 0; i < 4; ++i)S[i] = { (int)round(sz*(S[i].x*ca - S[i].y*sa) + x),(int)round(sz*(S[i].x*sa + S[i].y*ca) + y) };
		setd(ps1, pw1, pc1);
		setf(fc1);
		ppolygon(S, 4);
		for (int i = 0; i < 3; ++i)S[i] = t[i];
		for (int i = 0; i < 3; ++i)S[i] = { (int)round(sz*(S[i].x*ca - S[i].y*sa) + x),(int)round(sz*(S[i].x*sa + S[i].y*ca) + y) };
		setd(ps1, pw1, pc1);
		setf(fc2);
		ppolygon(S, 3);
		for (int i = 0; i < 3; ++i)S[i] = t[i], S[i].x = -S[i].x;
		for (int i = 0; i < 3; ++i)S[i] = { (int)round(sz*(S[i].x*ca - S[i].y*sa) + x),(int)round(sz*(S[i].x*sa + S[i].y*ca) + y) };
		setd(ps1, pw1, pc1);
		setf(fc2);
		ppolygon(S, 3);
	}
}enemy2demo;
class enemy4image {
private:
	int ps1, pw1; COLORREF pc1;
	int ps2, pw2; COLORREF pc2;
	double x, y;
	double sz;
public:
	COLORREF fc1, fc2;
	double angle;
	double r, r2;
	enemy4image() {
		r = 30; r2 = 25;
		ps1 = 0; pw1 = 0; pc1 = rgb(130, 70, 200);
		ps2 = 0; pw2 = 0; pc2 = rgb(110, 50, 180);
		fc1 = rgb(130, 70, 200); fc2 = rgb(110, 50, 180);
		angle = 0; setsize(1.0);
		x = y = 0;
	}
	void setsize(double Sz) {
		sz = Sz; r = r * sz; r2 = r2 * sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		setd(ps1, pw1, pc1); setf(fc1);
		pcircle((int)round(x), (int)round(y), (int)round(r));
		setd(ps2, pw2, pc2); setf(fc2);
		pcircle((int)round(x+ca*3), (int)round(y+sa*3), (int)round(r2));
	}
}enemy4demo;
class boss1image {
private:
	double x, y;

	int ps1, pw1; COLORREF pc1;
	int ps2, pw2, pc2, fc2;
	double x1, y1, r1, x2, y2, r2;
	int ps3, pw3, pc3, fc3;
	double x3, y3, r3;
	double sz;
	COLORREF getrgbtsp(COLORREF c, COLORREF tsc, double tsp) {
		double r = GetRValue(c), g = GetGValue(c), b = GetBValue(c);
		double R = GetRValue(tsc), G = GetGValue(tsc), B = GetBValue(tsc);
		r = tsp * r + (1 - tsp) * R; g = tsp * g + (1 - tsp) * G; b = tsp * b + (1 - tsp) * B;
		return RGB((int)round(r), (int)round(g), (int)round(b));
	}
public:
	COLORREF fc1;
	double angle;
	double r;
	COLORREF tsc; double tsp;
	boss1image() {
		r = 50;
		ps1 = 0; pw1 = 0; pc1 = rgb(200, 80, 0);
		fc1 = rgb(200, 80, 30);
		ps2 = 0; pw2 = 3; pc2 = rgb(0, 0, 0);
		fc2 = rgb(220, 220, 220);
		ps3 = 0; pw3 = 2; pc3 = rgb(200, 80, 0);
		fc3 = rgb(220, 220, 220);
		angle = 0; setsize(1.0); settransparent(WHITE, 1.0);
		x = y = 0;
		x1 = r * 0.1; y1 = r * 0.4; r1 = r /4;
		x2 = r * 0.1; y2 = -r * 0.4; r2 = r /4;
		x3 = r / 1.1; y3 = 0; r3 = r / 3.6;
	}
	void setsize(double Sz) {
		sz = Sz; r = r * sz;
		x1 = x1 * sz; y1 = y1 * sz; r1 = r1 * sz;
		x2 = x2 * sz; y2 = y2 * sz; r2 = r2 * sz;
		x3 = x3 * sz; y3 = y3 * sz; r3 = r3 * sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void settransparent(COLORREF Tsc, double Tsp) {
		tsc = Tsc; tsp = Tsp;
	}
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		
		setd(ps3, pw3, getrgbtsp(pc3, tsc, tsp));
		setf(getrgbtsp(fc3, tsc, tsp));
		double X3 = x3 * ca - y3 * sa, Y3 = x3 * sa + y3 * ca;
		pcircle(x + X3, y + Y3, r3);

		setd(ps1, pw1, getrgbtsp(pc1, tsc, tsp));
		setf(getrgbtsp(fc1, tsc, tsp));
		pcircle((int)round(x), (int)round(y), (int)round(r));
		
		setd(ps2, pw2, getrgbtsp(pc2, tsc, tsp));
		setf(getrgbtsp(fc2, tsc, tsp));
		double X1 = x1 * ca - y1 * sa, Y1 = x1 * sa + y1 * ca;
		pcircle(x + X1, y + Y1, r1);
		double X2 = x2 * ca - y2 * sa, Y2 = x2 * sa + y2 * ca;
		pcircle(x + X2, y + Y2, r2);
	}
}boss1demo;
bool isobjid(int ID) {
	return (ID == IDTREE || ID == IDSTONE || ID == IDFRUIT || ID==IDTREE2);
}
bool isenemyid(int ID) /* without boss */{
	return (ID == IDENEMY1 || ID == IDENEMY2 || ID == IDENEMY3 || ID == IDENEMY4); 
}
double getenemyatk(int ID)/* without boss */ {
	if (ID == IDENEMY1) return 5;
	if (ID == IDENEMY2) return 3;
	if (ID == IDENEMY3) return 1;
	if (ID == IDENEMY4) return 2;
	return -1;
}
double getenemyR(int ID) {
	if (ID == IDENEMY1)return enemy1demo.r;
	if (ID == IDENEMY2)return enemy2demo.r;
	if (ID == IDENEMY3)return enemy3demo.r;
	if (ID == IDENEMY4)return enemy4demo.r;
	if (ID == IDBOSS1)return boss1demo.r;
	return -1;
}
double getenemylife(int ID) {
	if (ID == IDENEMY1) return 1;
	if (ID == IDENEMY2) return 1;
	if (ID == IDENEMY3) return 1;
	if (ID == IDENEMY4) return 2;
	if (ID == IDBOSS1)return 30;
	return -1;
}
void paintenemy(int ID, vector2 p, double ang) {
	if (ID == IDENEMY1) {
		enemy1demo.setposition(p.x, p.y);
		enemy1demo.angle = ang;
		enemy1demo.paint();
	}
	if (ID == IDENEMY2) {
		enemy2demo.setposition(p.x, p.y);
		enemy2demo.angle = ang;
		enemy2demo.paint();
	}
	if (ID == IDENEMY3) {
		enemy3demo.setposition(p.x, p.y);
		enemy3demo.angle = ang;
		enemy3demo.paint();
	}
	if (ID == IDENEMY4) {
		enemy4demo.setposition(p.x, p.y);
		enemy4demo.angle = ang;
		enemy4demo.paint();
	}
	if (ID == IDBOSS1) {
		boss1demo.setposition(p.x, p.y);
		boss1demo.angle = ang;
		boss1demo.paint();
	}
}
double getobjR(int ID) {
	if (ID == IDTREE)return treedemo.r;
	if (ID == IDSTONE)return stonedemo.r;
	if (ID == IDFRUIT)return fruitdemo.r;
	if (ID == IDTREE2)return tree2demo.r;
	return -1;
}
const double maxobjR = max(max(max(treedemo.r, stonedemo.r), fruitdemo.r),tree2demo.r);
const double maxenemyR /* without boss */ = max(max(enemy1demo.r, enemy2demo.r), max(enemy3demo.r, enemy4demo.r));