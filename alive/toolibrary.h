#pragma once
#include "winpaint.h"
#include <Windows.h>
#include <vector>
#include <utility>
using namespace std;
#define lgcenterhorizontal 0
#define lgleft 1
#define lgright 2
#define lgcentervertical 0
#define lgtop 4
#define lgbottom 8
_ABC arrABC[128];
class textbox {
public:
	COLORREF textcolor;
	bool ifhighlight; COLORREF highlightcolor;
	int fh, fw; LPCSTR flpf;
	LPCSTR text;
	BYTE layoutgravity;
	int x1, y1, x2, y2;
	int tx1, ty1, tx2, ty2;
	bool mouseover_, mouseover;
	bool lbuttonpress, lbuttonrelease;
	void init() {
		resethighlight();
		setstyle(BLACK, 0, 0, NULL, 0);
		text = NULL;
		setbox(0, 0, 0, 0);
		tx1 = ty1 = tx2 = ty2 = 0;
		mouseover_ = 0; mouseover = 0;
		lbuttonpress = 0;
		lbuttonrelease = 0;
	}
	void setbox(int X1, int Y1, int X2, int Y2) {
		x1 = X1, y1 = Y1, x2 = X2, y2 = Y2;
	}
	void setfont(int h, int w, LPCSTR lpf) {
		fh = h; fw = w; flpf = lpf;
	}
	void resethighlight() {
		ifhighlight = 0; highlightcolor = NULL;
	}
	void sethighlight(COLORREF hc) {
		ifhighlight = 1;
		highlightcolor = hc;
	}
	void setstyle(COLORREF tc, int h, int w, LPCSTR lpf, BYTE lgravity) {
		textcolor = tc;
		setfont(h, w, lpf);
		layoutgravity = lgravity;
	}
	void paint() {
		HDC hdc = _hDCMem;
		HFONT hfont = CreateFont(fh, fw, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, flpf);
		SetTextColor(hdc, textcolor);
		SelectObject(hdc, hfont);
		GetCharABCWidths(hdc, 0, 127, arrABC);
		int X = x1, Y = y1;
		BYTE lx = layoutgravity & 3, ly = layoutgravity >> 2;
		int width = 0;
		int height = fh;
		for (int i = 0; i < strlen(text); ++i) {
			_ABC p = arrABC[text[i]];
			width += p.abcA + p.abcB + p.abcC;
		}
		if (lx != lgleft) {
			if (lx == lgcenterhorizontal)X = (x1 + x2 - width) / 2; else
				if (lx == lgright)X = x2 - width;
		}
		if (ly != lgtop) {
			if (ly == lgcentervertical)Y = (y1 + y2 - height) / 2; else
				if (ly == lgbottom)Y = y2 - height;
		}
		tx1 = X; ty1 = Y; tx2 = X + width; ty2 = Y + height;
		if (ifhighlight) {
			HBRUSH hbrush = CreateSolidBrush(highlightcolor);
			SelectObject(hdc, hbrush);
			SelectObject(hdc, hnullpen);
			Rectangle(hdc, tx1 - 2, ty1, tx2 + 2, ty2);
			DeleteObject(hbrush);
		}
		TextOut(hdc, X, Y, text, strlen(text));
		DeleteObject(hfont);
	}
	void clear(COLORREF bc) {
		clearscreen(bc, tx1, ty1, tx2, ty2);
		tx1 = ty1 = tx2 = ty2 = 0;
	}
	bool ifmouseover() {
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		return (ms.x >= tx1 && ms.x <= tx2 && ms.y >= ty1 && ms.y <= ty2);
	}
	bool ifmouseovertranstrue() {
		return(!mouseover_ && mouseover);
	}
	bool ifmouseovertransfalse() {
		return(mouseover_ && !mouseover);
	}
	void listen() {
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		mouseover_ = mouseover;
		mouseover = (ms.x >= tx1 && ms.x <= tx2 && ms.y >= ty1 && ms.y <= ty2);
		lbuttonrelease = lbuttonpress && mouseover && islbuttonup();
		lbuttonpress = !lbuttonrelease && mouseover && (lbuttonpress || islbuttondown());
	}
};
class picker {
public:
	int r;
	int x1, y1, x2, y2;
	int x, y;
	bool mouseover_, mouseover, lbuttonpress, lbuttonrelease;
	bool picked, pickedtrans;
	vector<pair<POINT, COLORREF> > s;
	void init() {
		setstyle(3); setbox(0, 0, 0, 0);
		x = y = 0; 
		mouseover_ = 0; mouseover = 0;
		lbuttonpress = 0;
		lbuttonrelease = 0;
		picked = pickedtrans = 0;
		s.clear();
	}
	void setbox(int X1, int Y1, int X2, int Y2) {
		x1 = X1; y1 = Y1; x2 = X2; y2 = Y2;
	}
	void setstyle(int R) { r = R; }
	bool ifmouseover() {
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		return (ms.x >= x1 && ms.x <= x2 && ms.y >= y1 && ms.y <= y2);
	}
	bool ifmouseovertranstrue() {
		return(!mouseover_ && mouseover);
	}
	bool ifmouseovertransfalse() {
		return(mouseover_ && !mouseover);
	}
	void visibletrans() {
		if (!picked || s.empty())return;
		for (vector<pair<POINT, COLORREF> >::iterator it = s.begin(); it != s.end(); it++) {
			int x = (*it).first.x, y = (*it).first.y;
			pdot(x, y, (*it).second);
		}
	}
#define setr setstyle
	void listen() {
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		mouseover_ = mouseover;
		mouseover = (ms.x >= x1 && ms.x <= x2 && ms.y >= y1 && ms.y <= y2);
		if (ifmouseovertransfalse() && lbuttonpress) {
			if (ms.x < x1)ms.x = x1; if (ms.x > x2)ms.x = x2;
			if (ms.y < y1)ms.y = y1; if (ms.y > y2)ms.y = y2;
			setmousexy(ms);
			mouseover = 1;
		}
		lbuttonrelease = lbuttonpress && mouseover && islbuttonup();
		lbuttonpress = !lbuttonrelease && mouseover && (lbuttonpress || islbuttondown());
		if (mouseover&&lbuttonpress) {
			if (!picked)picked = 1; else {
				for (vector<pair<POINT, COLORREF> >::iterator it = s.begin(); it != s.end(); it++) {
					int x = (*it).first.x, y = (*it).first.y;
					pdot(x, y, (*it).second);
				}
				s.clear();
			}
			pickedtrans = 1;
			x = ms.x, y = ms.y;
			for (int xx = -r; xx <= +r; ++xx) {
				int yy = (int)round(sqrt(r*r - xx * xx));
				if (abs(xx) > abs(yy))continue;
				if (x + xx >= x1 && x + xx <= x2) {
					POINT p1 = { x + xx,y + yy }, p2 = { x + xx,y - yy };
					if (p1.y >= y1 && p1.y <= y2)s.push_back(make_pair(p1, gdot(p1.x, p1.y)));
					if (p2.y >= y1 && p2.y <= y2)s.push_back(make_pair(p2, gdot(p2.x, p2.y)));
				}
				if (abs(xx) >= abs(yy))continue;
				if (y + xx >= y1 && y + xx <= y2) {
					POINT p1 = { x + yy,y + xx }, p2 = { x - yy,y + xx };
					if (p1.x >= x1 && p1.x <= x2)s.push_back(make_pair(p1, gdot(p1.x, p1.y)));
					if (p2.x >= x1 && p2.x <= x2)s.push_back(make_pair(p2, gdot(p2.x, p2.y)));
				}
			}
			for (vector<pair<POINT, COLORREF> >::iterator it = s.begin(); it != s.end(); it++) {
				int x = (*it).first.x, y = (*it).first.y;
				pdot(x, y, inversecolor(gdot(x,y)));
			}
		}
		else pickedtrans = 0;
	}
};
class button {
public:
	COLORREF textcolor[3], buttoncolor[3];
	int fh, fw; LPCSTR flpf;
	LPCSTR text;
	int x1, y1, x2, y2;
	bool mouseover_, mouseover;
	bool lbuttonpress, lbuttonrelease;
	void init() {
		textcolor[0] = textcolor[1] = textcolor[2] = BLACK;
		buttoncolor[0] = buttoncolor[1] = buttoncolor[2] = WHITE;
		setstyle(BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, 0, 0, "");
		text = NULL;
		setbox(0, 0, 0, 0);
		mouseover_ = 0; mouseover = 0;
		lbuttonpress = 0;
		lbuttonrelease = 0;
	}
	void setbox(int X1, int Y1, int X2, int Y2) {
		x1 = X1, y1 = Y1, x2 = X2, y2 = Y2;
	}
	void setfont(int h, int w, LPCSTR lpf) {
		fh = h; fw = w; flpf = lpf;
	}
	void setcolor(COLORREF tc1, COLORREF tc2, COLORREF tc3, COLORREF bc1, COLORREF bc2, COLORREF bc3) {
		textcolor[0] = tc1; textcolor[1] = tc1; textcolor[2] = tc3;
		buttoncolor[0] = bc1; buttoncolor[1] = bc2; buttoncolor[2] = bc3;
	}
	void setstyle(COLORREF tc1, COLORREF tc2, COLORREF tc3, COLORREF bc1, COLORREF bc2, COLORREF bc3, int h, int w, LPCSTR lpf) {
		setfont(h, w, lpf);
		setcolor(tc1, tc2, tc3, bc1, bc2, bc3);
	}
	bool ifmouseover() {
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		return (ms.x >= x1 && ms.x <= x2 && ms.y >= y1 && ms.y <= y2);
	}
	bool ifmouseovertranstrue() {
		return(!mouseover_ && mouseover);
	}
	bool ifmouseovertransfalse() {
		return(mouseover_ && !mouseover);
	}
	void paint(int id = -1) {
		if (id == -1) {
			id = 0;
			if (mouseover)id = 1;
			if (lbuttonpress)id = 2;
		}
		HDC hdc = _hDCMem;
		HBRUSH hbrush = CreateSolidBrush(buttoncolor[id]);
		SelectObject(hdc, hbrush);
		SelectObject(hdc, hnullpen);
		Rectangle(hdc, x1,y1,x2,y2);
		DeleteObject(hbrush);
		if (text == NULL)return;
		HFONT hfont = CreateFont(fh, fw, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, flpf);
		SetTextColor(hdc, textcolor[id]);
		SelectObject(hdc, hfont);
		GetCharABCWidths(hdc, 0, 127, arrABC);
		int X = x1, Y = y1;
		int width = 0;
		int height = fh;
		for (int i = 0; i < strlen(text); ++i) {
			_ABC p = arrABC[text[i]];
			width += p.abcA + p.abcB + p.abcC;
		}
		X = (x1 + x2 - width) / 2;
		Y = (y1 + y2 - height) / 2;
		TextOut(hdc, X, Y, text, strlen(text));
		DeleteObject(hfont);
	}
	void listen() {
		POINT ms = { getmousex(hwnd),getmousey(hwnd) };
		mouseover_ = mouseover;
		mouseover = (ms.x >= x1 && ms.x <= x2 && ms.y >= y1 && ms.y <= y2);
		lbuttonrelease = lbuttonpress && mouseover && islbuttonup();
		lbuttonpress = !lbuttonrelease && mouseover && (lbuttonpress || islbuttondown());
		if (ifmouseovertransfalse())paint(0); else
			if (lbuttonpress)paint(2); else
				if (ifmouseovertranstrue())paint(1);
	}
};