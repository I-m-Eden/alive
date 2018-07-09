#pragma once
#include "winpaint.h"
#include <windows.h>
#include <cmath>
#include <iostream>
using namespace std;
const int IDTREE = 1;
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
public:
	int px, py;
	int x1, y1, r1; COLORREF fc1;
	int x21, y21, x22, y22, d2; COLORREF fc2;
	int x31, y31, x32, y32, d3; COLORREF fc3;
	double angle;
	figureimage() { 
		x1 = y1 = 0; r1 = 40; fc1 = RGB(10, 10, 10);
		x21 = -20; y21 = 2; x22 = -15; y22 = -13; d2 = 22; fc2 = RGB(20, 20, 20);
		x31 = -7; y31 = -39; x32 = 7; y32 = -37; d3 = 17; fc3 = RGB(20, 20, 20);
		angle = 0;
	}
	void setposition(int x, int y) { px = x; py = y; }
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
public:
	int ps, pw, pc;
	int fc;
	int r;
	int x, y;
	treeimage() {
		ps = 0; pw = 0; pc = BLACK;
		fc = 0x85DA2F;
		r = 50;
	}
	void setposition(int X, int Y) {
		x = X; y = Y;
	}
	void paint() {
		setd(ps, pw, pc);
		setf(fc);
		pcircle(x, y, r);
	}
}treedemo;