#pragma once
#include "head.h"
#include "winpaint.h"
using namespace std;
const int IDTREE = 1;
const int IDSTONE = 2;
const int IDFRUIT = 5;
const int IDENEMY = 3;
const int IDENEMY2 = 4;
const int IDENEMY3 = 6;
class figureimage {
private:
	void drawellipse(COLORREF fc, double x1, double y1, double x2, double y2, int d) {
		int varX = (int)round( (sqrt(d*d - (y2 - y1)*(y2 - y1)) - fabs(x2 - x1) / 2) );
		int XL = min(x1, x2) - varX, XR = max(x1, x2) + varX;
		int varY = (int)round( (sqrt(d*d - (x2 - x1)*(x2 - x1)) - fabs(y2 - y1) / 2) );
		int YL = min(y1, y2) - varY, YR = max(y1, y2) + varY;
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
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		int X1 = (int)round(ca*x1 - sa * y1), Y1 = (int)round(sa*x1 + ca * y1);
		setf(fc1);
		fcircle(px + X1, py + Y1, r1);
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
	int r;
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
		pcircle(x, y, r);
	}
}treedemo;
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
		pcircle(x, y, r);
	}
}stonedemo;
class fruitimage {
private:
	int ps, pw; COLORREF pc, spc;
	double x, y;
public:
	COLORREF fc, sfc;
	int r, sr;
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
		pcircle(x, y, r);
		setd(ps, pw, spc);
		setf(sfc);
		pcircle(x, y, sr);
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
}enemydemo(0.5), enemy3demo(0.2);
class bulletimage {
private:
	double x, y;
public:
	COLORREF fc;
	int r;
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
		fcircle(x, y, r);
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