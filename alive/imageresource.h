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
const int IDENEMY5 = 10;
const int IDBULLET = 11;
const int IDBULLET2 = 12;
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
		ps = 0; pw = 2; pc = RGB(20, 150, 20);
		fc = RGB(90,220,90);
		r = 46;
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
		ps = 0; pw = 3; pc = RGB(30,130,0);
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
		ps = 0; pw = 2; pc = rgb(100, 100, 100);
		fc = RGB(170, 170, 170);
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
class enemy1image {
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
	double RW, RH, R;
	COLORREF FC1, FC2, PC1, PC2; double SZ;
public:
	COLORREF fc1, fc2;
	double angle;
	double rw, rh, r;
	enemy1image(double sz) {
		SZ = sz;
		RW = rw = 42.0*sz; RH = rh = 65.0*sz; R = r = min(rw, rh);
		ps1 = 0; pw1 = 0; PC1 = pc1 = 0x788870;
		FC1 = fc1 = 0xA0B0A0;
		ps2 = 0; pw2 = 0; PC2 = pc2 = 0xB2EB79;
		FC2 = fc2 = 0x8FCF4F;
		angle = 0;
		x = y = 0;
		for (int i = Sn / 2 + 1; i < Sn; ++i)
			s[i] = s[Sn - i], s[i].x = -s[i].x;
	}
	void setsize(double Sz) {
		sz = SZ * Sz; rw = RW * Sz; rh = RH * Sz; r = R * Sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void mixcolor(COLORREF c, double pct) {
		fc1 = mixrgb(FC1, c, pct);
		fc2 = mixrgb(FC2, c, pct);
		pc1 = mixrgb(PC1, c, pct);
		pc2 = mixrgb(PC2, c, pct);
	}
	void resetcolor() {
		fc1 = FC1; fc2 = FC2; 
		pc1 = PC1; pc2 = PC2;
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
class bullet2image {
private:
	double x, y;
public:
	COLORREF fc;
	double r;
	bullet2image() {
		fc = RGB(20, 120, 100);
		r = 4;
		x = y = 0;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void paint() {
		setf(fc);
		fcircle((int)round(x), (int)round(y), (int)round(r));
	}
}bullet2demo;
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
	COLORREF FC1, FC2, PC1, PC2;
	double RW, RH, R; double SZ;
public:
	COLORREF fc1, fc2;
	double angle;
	double rw, rh, r;
	enemy2image(double Sz) {
		SZ = sz = Sz; RW = rw = 30.0*sz; RH = rh = 35.0*sz; R = r = min(rw, rh);
		ps1 = 0; pw1 = 0; PC1 = pc1 = 0x788870;
		FC1 = fc1 = rgb(237, 220, 12);
		ps2 = 0; pw2 = 0; PC2 = pc2 = 0xB2EB79;
		FC2 = fc2 = rgb(240, 187, 77);
		angle = 0; 
		x = y = 0;
	}
	void setsize(double Sz) {
		sz = SZ * Sz; rw = RW * Sz; rh = RH * Sz; r = R * Sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void mixcolor(COLORREF c, double pct) {
		fc1 = mixrgb(FC1, c, pct);
		fc2 = mixrgb(FC2, c, pct);
		pc1 = mixrgb(PC1, c, pct);
		pc2 = mixrgb(PC2, c, pct);
	}
	void resetcolor() {
		fc1 = FC1; fc2 = FC2; pc1 = PC1; pc2 = PC2;
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
}enemy2demo(0.5);
class enemy4image {
private:
	int ps1, pw1; COLORREF pc1;
	int ps2, pw2; COLORREF pc2;
	double x, y;
	double sz;
	COLORREF FC1, FC2, FC3, FC4, PC1, PC2;
	double R, R2; double SZ;
public:
	COLORREF fc1, fc2, fc3, fc4;
	double angle;
	double r, r2;
	enemy4image() {
		SZ = sz = 1.0;
		R = r = 30 * sz; R2 = r2 = 25 * sz;
		ps1 = 0; pw1 = 0; PC1 = pc1 = rgb(130, 70, 200);
		ps2 = 0; pw2 = 0; PC2 = pc2 = rgb(110, 50, 180);
		FC1 = fc1 = rgb(130, 70, 200); FC2 = fc2 = rgb(110, 50, 180);
		FC3 = fc3 = rgb(90, 30, 160); FC4 = fc4 = rgb(70, 10, 140);
		angle = 0;
		x = y = 0;
	}
	void switchfc() {
		swap(fc1, fc2); swap(FC1, FC2);
		swap(fc3, fc4); swap(FC3, FC4);
	}
	void setsize(double Sz) {
		sz = sz * Sz; r = R * Sz; r2 = R2 * Sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void mixcolor(COLORREF c, double pct) {
		fc1 = mixrgb(FC1, c, pct);
		fc2 = mixrgb(FC2, c, pct);
		fc3 = mixrgb(FC3, c, pct);
		fc4 = mixrgb(FC4, c, pct);
		pc1 = mixrgb(PC1, c, pct);
		pc2 = mixrgb(PC2, c, pct);
	}
	void resetcolor() {
		fc1 = FC1; fc2 = FC2; fc3 = FC3; fc4 = FC4;
		pc1 = PC1; pc2 = PC2;
	}
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		setd(ps1, pw1, pc1); setf(fc1);
		pcircle((int)round(x), (int)round(y), (int)round(r));
		setd(ps2, pw2, pc2); setf(fc2);
		pcircle((int)round(x+ca*3), (int)round(y+sa*3), (int)round(r2));
	}
}enemy4demo;
class enemy5image {
private:
	void drawellipse(COLORREF fc, double x1, double y1, double x2, double y2, int d) {
		int varX = (int)round((sqrt(d*d - (y2 - y1)*(y2 - y1)) - fabs(x2 - x1) / 2));
		int XL = (int)round(min(x1, x2)) - varX, XR = (int)round(max(x1, x2)) + varX;
		int varY = (int)round((sqrt(d*d - (x2 - x1)*(x2 - x1)) - fabs(y2 - y1) / 2));
		int YL = (int)round(min(y1, y2)) - varY, YR = (int)round(max(y1, y2)) + varY;
		for (int X = XL; X <= XR; ++X)for (int Y = YL; Y <= YR; ++Y) {
			int dd = (int)round(sqrt((X - x1)*(X - x1) + (Y - y1)*(Y - y1)) + sqrt((X - x2)*(X - x2) + (Y - y2)*(Y - y2)));
			if (dd <= d)pdot(X, Y, fc);
		}
	}
	double x11, x12, y11, y12;
	int ps2, pw2; COLORREF pc2; double x2, y2;
	double x, y;
	double sz;
	COLORREF FC1, FC2, PC2;
	double R, D1, R2;
	double X11, X12, Y11, Y12, X2, Y2; double SZ;
public:
	COLORREF fc1, fc2;
	double angle;
	double r, d1, r2;
	enemy5image() {
		SZ = sz = 1.0;
		D1 = d1 = 60; R2 = r2 = 5; R = r = 20;
		ps2 = 0; pw2 = 0; PC2 = pc2 = rgb(110, 110, 180);
		FC1 = fc1 = rgb(0, 200, 200); FC2 = fc2 = rgb(110, 110, 180);
		angle = 0; setsize(1.0);
		X11 = x11 = 0; Y11 = y11 = -25; X12 = x12 = 0; Y12 = y12 = 25;
		X2 = x2 = 0; Y2 = y2 = -13;
	}
	void setsize(double Sz) {
		sz = sz * Sz; r = R * Sz; d1 = D1 * Sz; r2 = R2 * Sz;
		x11 = X11 * Sz; x12 = X12 * Sz; y11 = Y11 * Sz; y12 = Y12 * Sz;
		x2 = X2 * Sz; y2 = Y2 * Sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void mixcolor(COLORREF c, double pct) {
		fc1 = mixrgb(FC1, c, pct);
		fc2 = mixrgb(FC2, c, pct);
		pc2 = mixrgb(PC2, c, pct);
	}
	void resetcolor() {
		fc1 = FC1; fc2 = FC2; pc2 = PC2;
	}
	void paint() {
		double ca = cos(angle), sa = sin(angle);
		double X11 = x11 * ca - y11 * sa, Y11 = x11 * sa + y11 * ca;
		double X12 = x12 * ca - y12 * sa, Y12 = x12 * sa + y12 * ca;
		drawellipse(fc1, X11 + x, Y11 + y, X12 + x, Y12 + y, d1);
		setd(ps2, pw2, pc2); setf(fc2);
		double X21 = x2 * ca - y2 * sa, Y21 = x2 * sa + y2 * ca;
		double X22 = -X21, Y22 = -Y21;
		pcircle((int)round(X21 + x), (int)round(Y21 + y), r2);
		pcircle((int)round(X22 + x), (int)round(Y22 + y), r2);
	}
}enemy5demo;
class boss1image {
private:
	BYTE pt[130][130][3];
	double x, y;
	int ps1, pw1; COLORREF pc1;
	int ps2, pw2, pc2;
	double x1, y1, r1, x2, y2, r2;
	int ps3, pw3, pc3;
	double x3, y3, r3;
	double sz;
	void getrgbtsp(BYTE&r, BYTE&g, BYTE&b, BYTE  R, BYTE G, BYTE B, double tsp) {
		r = BYTE(tsp * r + (1 - tsp) * R); 
		g = BYTE(tsp * g + (1 - tsp) * G); 
		b = BYTE(tsp * b + (1 - tsp) * B);
	}
	COLORREF PC1, PC2, PC3;
	COLORREF FC1, FC2, FC3;
public:
	COLORREF fc1, fc2, fc3;
	double angle;
	double r; int R;
	double tsp;
	boss1image() {
		r = 50; R = (int)round(r + 10);
		ps1 = 0; pw1 = 0; PC1 = pc1 = rgb(200, 80, 0);
		FC1 = fc1 = rgb(200, 80, 30);
		ps2 = 0; pw2 = 3; PC2 = pc2 = rgb(0, 0, 0);
		FC2 = fc2 = rgb(220, 220, 220);
		ps3 = 0; pw3 = 2; PC3 = pc3 = rgb(200, 80, 0);
		FC3 = fc3 = rgb(220, 220, 220);
		angle = 0; setsize(1.0); settransparent(1.0);
		x = y = 0;
		x1 = r * 0.1; y1 = r * 0.4; r1 = r /4;
		x2 = r * 0.1; y2 = -r * 0.4; r2 = r /4;
		x3 = r / 1.1; y3 = 0; r3 = r / 3.6;
	}
	void setsize(double Sz) {
		sz = Sz; r = r * sz; R = (int)round(R * sz);
		x1 = x1 * sz; y1 = y1 * sz; r1 = r1 * sz;
		x2 = x2 * sz; y2 = y2 * sz; r2 = r2 * sz;
		x3 = x3 * sz; y3 = y3 * sz; r3 = r3 * sz;
	}
	void setposition(double X, double Y) {
		x = X; y = Y;
	}
	void settransparent(double Tsp) {
		tsp = Tsp;
	}
	void mixcolor(COLORREF c, double pct) {
		fc1 = mixrgb(FC1, c, pct);
		fc2 = mixrgb(FC2, c, pct);
		fc3 = mixrgb(FC3, c, pct);
		pc1 = mixrgb(PC1, c, pct);
		pc2 = mixrgb(PC2, c, pct);
		pc3 = mixrgb(PC3, c, pct);
	}
	void resetcolor() {
		fc1 = FC1; fc2 = FC2; fc3 = FC3;
		pc1 = PC1; pc2 = PC2; pc3 = PC3;
	}
	void paint() {
		if (fabs(tsp - 1.0) > 1e-4) {
			beginPdot();
			for (int dx = 0; dx <= R + R; dx++)
				for (int dy = 0; dy <= R + R; dy++)
					Gdot(x + dx - R, y + dy - R, pt[dx][dy][0], pt[dx][dy][1], pt[dx][dy][2]);
			endPdot();
		}
		double ca = cos(angle), sa = sin(angle);
		
		setd(ps3, pw3, pc3);
		setf(fc3);
		double X3 = x3 * ca - y3 * sa, Y3 = x3 * sa + y3 * ca;
		pcircle(x + X3, y + Y3, r3);

		setd(ps1, pw1, pc1);
		setf(fc1);
		pcircle((int)round(x), (int)round(y), (int)round(r));
		
		setd(ps2, pw2, pc2);
		setf(fc2);
		double X1 = x1 * ca - y1 * sa, Y1 = x1 * sa + y1 * ca;
		pcircle(x + X1, y + Y1, r1);
		double X2 = x2 * ca - y2 * sa, Y2 = x2 * sa + y2 * ca;
		pcircle(x + X2, y + Y2, r2);

		if (fabs(tsp - 1.0) > 1e-4) {
			beginPdot();
			for (int dx = 0; dx <= R + R; dx++)
				for (int dy = 0; dy <= R + R; dy++) {
					BYTE r = 0, g = 0, b = 0; Gdot(x + dx - R, y + dy - R, r, g, b);
					getrgbtsp(r, g, b, pt[dx][dy][0], pt[dx][dy][1], pt[dx][dy][2], tsp);
					Pdot(x + dx - R, y + dy - R, r, g, b);
				}
			endPdot();
		}
	}
}boss1demo;
bool isbulletid(int ID) {
	return (ID == IDBULLET || ID == IDBULLET2);
}
bool isenemybulletid(int ID) {
	return (ID == IDBULLET2);
}
bool isobjid(int ID) {
	return (ID == IDTREE || ID == IDSTONE || ID == IDFRUIT || ID==IDTREE2);
}
bool isenemyid(int ID) /* without boss */{
	return (ID == IDENEMY1 || ID == IDENEMY2 || ID == IDENEMY3 || ID == IDENEMY4 || ID == IDENEMY5);
}
double getenemyatk(int ID)/* without boss */ {
	if (ID == IDENEMY1) return 5;
	if (ID == IDENEMY2) return 3;
	if (ID == IDENEMY3) return 1;
	if (ID == IDENEMY4) return 2;
	if (ID == IDENEMY5) return 4;
	return -1;
}
double getenemyR(int ID) {
	if (ID == IDENEMY1)return enemy1demo.r;
	if (ID == IDENEMY2)return enemy2demo.r;
	if (ID == IDENEMY3)return enemy3demo.r;
	if (ID == IDENEMY4)return enemy4demo.r;
	if (ID == IDBOSS1)return boss1demo.r;
	if (ID == IDENEMY5)return enemy5demo.r;
	return -1;
}
double getenemylife(int ID) {
	if (ID == IDENEMY1) return 1;
	if (ID == IDENEMY2) return 1;
	if (ID == IDENEMY3) return 1;
	if (ID == IDENEMY4) return 2;
	if (ID == IDBOSS1)return 50;
	if (ID == IDENEMY5)return 3;
	return -1;
}
void paintenemy(int ID, vector2 p, double ang, double pct = 1.0, COLORREF bkc = 0, double sz = 1.0) {
	if (ID == IDENEMY1) {
		enemy1demo.setposition(p.x, p.y);
		enemy1demo.angle = ang;
		enemy1demo.mixcolor(bkc, pct);
		enemy1demo.setsize(sz);
		enemy1demo.paint();
		enemy1demo.resetcolor();
	}
	if (ID == IDENEMY2) {
		enemy2demo.setposition(p.x, p.y);
		enemy2demo.angle = ang;
		enemy2demo.mixcolor(bkc, pct);
		enemy2demo.setsize(sz);
		enemy2demo.paint();
		enemy2demo.resetcolor();
	}
	if (ID == IDENEMY3) {
		enemy3demo.setposition(p.x, p.y);
		enemy3demo.angle = ang;
		enemy3demo.mixcolor(bkc, pct);
		enemy3demo.setsize(sz);
		enemy3demo.paint();
		enemy3demo.resetcolor();
	}
	if (ID == IDENEMY4) {
		enemy4demo.setposition(p.x, p.y);
		enemy4demo.angle = ang;
		enemy4demo.mixcolor(bkc, pct);
		enemy4demo.setsize(sz);
		enemy4demo.paint();
		enemy4demo.resetcolor();
	}
	if (ID == IDBOSS1) {
		boss1demo.setposition(p.x, p.y);
		boss1demo.angle = ang;
		boss1demo.mixcolor(bkc, pct);
		boss1demo.setsize(sz);
		boss1demo.paint();
		boss1demo.resetcolor();
	}
	if (ID == IDENEMY5) {
		enemy5demo.setposition(p.x, p.y);
		enemy5demo.angle = ang;
		enemy5demo.mixcolor(bkc, pct);
		enemy5demo.setsize(sz);
		enemy5demo.paint();
		enemy5demo.resetcolor();
	}
}
double getobjR(int ID) {
	if (ID == IDTREE)return treedemo.r;
	if (ID == IDSTONE)return stonedemo.r;
	if (ID == IDFRUIT)return fruitdemo.r;
	if (ID == IDTREE2)return tree2demo.r;
	return -1;
}
double getbulletR(int ID) {
	if (ID == IDBULLET)return bulletdemo.r;
	if (ID == IDBULLET2)return bullet2demo.r;
	return -1;
}
double getenemybulletvelocity(int ID) {
	if (ID == IDBULLET2)return 5;
	return -1;
}
double getenemybulletrange(int ID) {
	if (ID == IDBULLET2)return 800;
	return -1;
}
double getenemybulletatk(int ID) {
	if (ID == IDBULLET2)return 1;
	return -1;
}
void paintbullet(int ID, vector2 p) {
	if (ID == IDBULLET) {
		bulletdemo.setposition(p.x, p.y);
		bulletdemo.paint();
	}
	if (ID == IDBULLET2) {
		bullet2demo.setposition(p.x, p.y);
		bullet2demo.paint();
	}
}
const double maxobjR = max(max(max(treedemo.r, stonedemo.r), fruitdemo.r),tree2demo.r);
const double maxenemyR /* without boss */ = max(max(max(enemy1demo.r, enemy2demo.r), max(enemy3demo.r, enemy4demo.r)), enemy5demo.r);