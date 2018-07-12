//
//	source.cpp
//	ALIVE
//
//	Created by Eden on 17/5/18.
//	Copyright © 2018年 author. All rights reserved.
//
//
//	用Visual Studio 2017编译之前注意事项：
//	项目属性->c/c++->预处理器->预处理器定义 中添加：
//	_CRT_SECURE_NO_DEPRECATE
//	_CRT_NONSTDC_NO_DEPRECATE
//	项目属性->c/c++->代码生成->运行库 修改为 "多线程调试 (/MTd)"
//
#include <ctime>
#include <utility>
#include <afxwin.h>
#include "vector2.h"
#include "resource.h"
#include "winpaint.h"
#include "toolibrary.h"
#include "coloresource.h"
#include "imageresource.h"
using namespace std;
#define ref(i,x,y)for(int i=(x);i<=(y);++i)
#define def(i,x,y)for(int i=(x);i>=(y);--i)
const double pi = acos(-1);
string constr(int s) {
	string res = "";
	if (s < 0)res = "-" + constr(-s); else
		if (s < 10)res = res + char(s + 48); else
			res = constr(s / 10), res = res + char(s % 10 + 48);
	return res;
}
void flushmouse() { while (islbuttondown())delay(1); while (peekmsg())delay(1); }
void flushkey() { FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); }
void _resume() {
}

figureimage figure;
vector2 realp;
vector<pair<vector2, int> > mp;
typedef vector<pair<vector2, int>>::iterator it_pvi;
vector<it_pvi> mpobj, mptch;
typedef vector<it_pvi>::iterator it_itpvi;
it_pvi gainobj; double gainpct;
vector<pair<vector2, int> > nullpvi; it_pvi null_itpvi;
void initnullitpvi() {
	nullpvi.clear(); nullpvi.push_back(make_pair(vector2(), -1)); 
	null_itpvi = nullpvi.begin();
}
bool sighted(vector2 p, int name) {
	if (name == IDTREE) return (p.x >= -treedemo.r&&p.x <= _winw + treedemo.r&&p.y >= -treedemo.r&&p.y <= _winh + treedemo.r);
	if (name == IDSTONE) return (p.x >= -stonedemo.r&&p.x <= _winw + stonedemo.r&&p.y >= -stonedemo.r&&p.y <= _winh + stonedemo.r);
}
void producemap() {
	mp.clear();
	ref(i, 1, 1000)mp.push_back(make_pair(vector2(rand() % 12000 - 6000,rand() % 12000 - 6000), IDTREE));
	ref(i, 1, 2000)mp.push_back(make_pair(vector2(rand() % 12000 - 6000, rand() % 12000 - 6000), IDSTONE));	
}
void paintmap() {
	setd(0, 0, GRAY170);
	for (int i = 0, X = (20 - int(realp.x) % 20); i < 40; ++i, X += 20)
		pline(X, 0, X, _winh);
	for (int i = 0, Y = (20 - int(realp.y) % 20); i < 30; ++i, Y += 20)
		pline(0, Y, _winw, Y);
	for (it_itpvi i = mpobj.begin(); i != mpobj.end(); i++) {
		pair<vector2, int> obj = (**i); vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (name == IDSTONE) {
			stonedemo.setposition(p.x, p.y);
			if (obj == *gainobj) {
				COLORREF c = stonedemo.fc; BYTE R = GetRValue(c), G = GetGValue(c), B = GetBValue(c);
				COLORREF cc = RGB(R*(1 - gainpct), G*(1 - gainpct), B*(1 - gainpct));
				stonedemo.fc = cc;
				stonedemo.paint();
				stonedemo.fc = c;
			}else stonedemo.paint();
		}
	}
	for (it_itpvi i = mpobj.begin(); i != mpobj.end(); i++) {
		pair<vector2, int> obj = (**i); vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (name == IDTREE) {
			treedemo.setposition(p.x, p.y);
			if (obj == *gainobj) {
				COLORREF c = treedemo.fc; BYTE R = GetRValue(c), G = GetGValue(c), B = GetBValue(c);
				COLORREF cc = RGB(R*(1 - gainpct), G*(1 - gainpct), B*(1 - gainpct));
				treedemo.fc = cc;
				treedemo.paint();
				treedemo.fc = c;
			}
			else treedemo.paint();
		}
	}
}
void paintmist(double p) {
	beginPdot();
	double q = 1.0 - p; p = p * 150;
	for (int i = _pDataSize - 1; i >= 0; --i) {
		BYTE&P = _pData[i];
		P = (BYTE)(q*P + p);
	}
	endPdot();
}
/*
void paintgaining(it_pvi obj, double pct) {
	if (*obj == *null_itpvi || pct <= 0)return;
	vector2 p = (*obj).first - realp + vector2(_winw / 2, _winh / 2); int name = (*obj).second;
	if (name == IDTREE) {
		setf(0x68B11F);
		fpie(p.x - treedemo.r, p.y - treedemo.r, p.x + treedemo.r, p.y + treedemo.r, 
			p.x + 1, p.y, p.x + cos(pct)*100, p.y - sin(pct)*100);
	}
	if (name == IDSTONE) {
		setf(0x727272);
		fpie(p.x - stonedemo.r, p.y - stonedemo.r, p.x + stonedemo.r, p.y + stonedemo.r, 
			p.x + 1, p.y, p.x + cos(pct)*100, p.y - sin(pct)*100);
	}
}
*/
void getsighted() {
	mpobj.clear();
	for (it_pvi i = mp.begin(); i != mp.end(); i++) {
		pair<vector2, int> obj = (*i); vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (!sighted(p, name))continue;
		mpobj.push_back(i);
	}
}
void gettouch() {
	mptch.clear();
	for (it_itpvi i = mpobj.begin(); i != mpobj.end(); i++) {
		pair<vector2, int> obj = (**i); vector2 p = obj.first - realp; int name = obj.second;
		double normp = norm(p);
		if (name == IDSTONE && norm(p) >= stonedemo.r + figuredemo.r1 - 1)continue;
		if (name == IDTREE && norm(p) >= treedemo.r + figuredemo.r1 - 1)continue;
		mptch.push_back(*i);
	}
}
void eraseall(it_pvi it) {
	mp.erase(it);
	getsighted(); gettouch();
}
void adjust(vector2&v) {
	double a0 = 1e9, a1 = 1e9;
	double normv = norm(v);
	for (it_itpvi i = mptch.begin(); i != mptch.end(); i++) {
		pair<vector2, int> obj = (**i); vector2 p = obj.first - realp; int name = obj.second;
		double normp = norm(p);
		if (name == IDSTONE) {
			if ((v*p) < 0)continue;
			if ((v^p) >= 0) a0 = min(a0, acos((v*p) / normv / normp));
			else a1 = min(a1, acos((v*p) / normv / normp));
		}
		if (name == IDTREE) {
			if ((v*p) < 0)continue;
			if ((v^p) >= 0) a0 = min(a0, acos((v*p) / normv / normp));
			else a1 = min(a1, acos((v*p) / normv / normp));
		}
	}
	if (a0 > pi / 2 && a1 > pi / 2)return;
	if (a0 <= pi / 2 && a1 <= pi / 2) {
		v = vector2(0, 0); return;
	}
	if (a0 <= pi / 2) {
		double a = atan2(v.y, v.x) - (pi / 2 - a0);
		double nv = normv * cos(pi / 2 - a0);
		v = vector2(nv*cos(a), nv*sin(a)); return;
	}
	if (a1 <= pi / 2) {
		double a = atan2(v.y, v.x) + (pi / 2 - a1);
		double nv = normv * cos(pi / 2 - a1);
		v = vector2(nv*cos(a), nv*sin(a)); return;
	}
}
BYTE*rcData;
string UseCustomResource(int rcId) {
	HRSRC hRsrc = FindResource(_hinst, MAKEINTRESOURCE(rcId), RT_BITMAP);
	if (NULL == hRsrc) return "rcError1";
	DWORD dwSize = SizeofResource(_hinst, hRsrc);
	if (0 == dwSize) return "rcError2";
	HGLOBAL hGlobal = LoadResource(_hinst, hRsrc);
	if (NULL == hGlobal) return "rcError3"; 
	rcData = new BYTE[dwSize];
	ZeroMemory(rcData, sizeof(BYTE)*dwSize);
	CopyMemory(rcData, (PBYTE)LockResource(hGlobal), dwSize);
	return "";
}
tagRGBTRIPLE arrbitmap[800][600]; bool flagarr;

void paintbmp(int x,int y,int X,int Y) {
	int w = 800, h = 600;
	if (!flagarr) {
		string fileinfo = UseCustomResource(IDB_BITMAP1);
		int cnt = 54;
		def(j, h - 1, 0) {
			ref(i, 0, w - 1) {
				BYTE r = rcData[cnt++], b = rcData[cnt++], g = rcData[cnt++];
				arrbitmap[i][j] = { b,g,r };
			}
			ref(i, 1, (4 - w * 3 % 4) % 4)cnt++;
		}
		delete[] rcData;
	}
	beginPdot();
	ref(i, x, X)ref(j, y, Y) {
		int r = 0, g = 0, b = 0, t = 0;
		int p = 4 * j / h + 2;
		ref(I, max(i - p, 0), min(i + p, w - 1))ref(J, max(j - p, 0), min(j + p, h - 1)) {
			tagRGBTRIPLE c = arrbitmap[I][J];
			r += c.rgbtRed; g += c.rgbtGreen; b += c.rgbtBlue; t++;
		}
		r /= t; g /= t; b /= t;
		double q1 = 1.0*max(j - 300, 0) / 300;
		double q2 = 1.0 - max(1.0*(sqrt((i - 400)*(i - 400) + (j - 540)*(j - 540)) - 150) / 510, 0);
		q2 = q2 * q2 * q2;
		double q = q1;
		r = (1 - q)*r + q * 200; g = (1 - q)*g + q * 200; b = (1 - q)*b + q * 200;
		Pdot(i, j, r, g, b);
	}
	endPdot();
}
void _restart1() {
	flushmouse(); textbox TB;
	int number_wood = 0, number_stone = 0;
	figure.setposition(_winw / 2, _winh / 2);
	producemap();
	realp = { 0,0 };
	figure.angle = 0;
	int tick = 0;
	int fps = 50, t = 0, rest = 0; DWORD last = GetTickCount();
	double velocity = 2.0;

	initnullitpvi();
	gainobj = null_itpvi; gainpct = 0;

	while (!_isquit) {
		tick++;

		vector2 ms = vector2(getmousex(hwnd) - _winw / 2, getmousey(hwnd) - _winh / 2);
		figure.angle = atan2(ms.y, ms.x) + pi / 2;

		vector2 v;
		if (!iswndactive()) {
			while (!iswndactive()) peekmsg(), delay(1);
			last = GetTickCount();
			flushkey(); flushmouse();
			while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) peekmsg(), delay(1);
		}
		if (GetAsyncKeyState('W') & 0x8000)v.y -= 1;
		if (GetAsyncKeyState('S') & 0x8000)v.y += 1;
		if (GetAsyncKeyState('A') & 0x8000)v.x -= 1;
		if (GetAsyncKeyState('D') & 0x8000)v.x += 1;
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;
		if (v.x || v.y) v = v * (velocity / norm(v));

		getsighted();
		gettouch();
		ref(times, 0, 1)adjust(v);
		realp = realp + v;

		if (GetAsyncKeyState('Q') & 0x8000) {
			it_pvi id = null_itpvi;
			for (it_itpvi i = mptch.begin(); i != mptch.end(); i++)
				if ((**i) == (*gainobj)) { id = *i; break; }
			if (*id != *null_itpvi) gainpct += 1.0 / 240; else {
				for (it_itpvi i = mptch.begin(); i != mptch.end(); i++) {
					int name = (**i).second;
					if (name == IDTREE || name == IDSTONE) { id = *i; break; }
				}
				gainpct = 0;
			}
			gainobj = id;
			if (gainpct >= 0.5) {
				if ((*gainobj).second == IDTREE) number_wood++; else number_stone++;
				eraseall(gainobj);
				gainobj = null_itpvi; gainpct = 0;
			}
		}
		else gainobj = null_itpvi, gainpct = 0;

		t++;
		clearscreen(GRAY200);
		paintmap();
		figure.paint();
		paintmist(0.25*sin(2 * pi*tick / 500) + 0.5);

		if (GetTickCount() >= last + 1000) { last += 1000; rest = t; t = 0; }
		sett(GRAY80, 30, 0, "");
		ptext(0, 0, ("fps: " + constr(rest)).c_str());
		TB.init();
		TB.setbox(0, 0, _winw, _winh);
		TB.setstyle(rgb(50, 100, 0), 30, 0, "", lgright | lgtop);
		string snw = "Number Of Wood: "; snw += constr(number_wood);
		TB.text = snw.c_str();
		TB.paint();
		TB.setbox(0, TB.ty2, _winw, _winh);
		TB.setstyle(rgb(50, 100, 0), 30, 0, "", lgright | lgtop);
		string sns = "Number Of Stone: "; sns += constr(number_stone);
		TB.text = sns.c_str();
		TB.paint();
		flushpaint();
		peekmsg(); delay(1);
	}
}
int Sr[800][600],Sg[800][600],Sb[800][600];
void Paintbmp(int x, int y, int X, int Y) {
	int w = 800, h = 600;
	if (!flagarr) {
		string fileinfo = UseCustomResource(IDB_BITMAP1);
		int cnt = 54;
		def(j, h - 1, 0) {
			ref(i, 0, w - 1) {
				BYTE r = rcData[cnt++], b = rcData[cnt++], g = rcData[cnt++];
				arrbitmap[i][j] = { b,g,r };
			}
			ref(i, 1, (4 - w * 3 % 4) % 4)cnt++;
		}
		delete[] rcData;
	}
	Sr[0][0] = arrbitmap[0][0].rgbtRed;
	Sg[0][0] = arrbitmap[0][0].rgbtGreen;
	Sb[0][0] = arrbitmap[0][0].rgbtBlue;
	for (int i = 1; i < 800; i++) Sr[i][0] = Sr[i - 1][0] + arrbitmap[i][0].rgbtRed;
	for (int i = 1; i < 800; i++) Sg[i][0] = Sg[i - 1][0] + arrbitmap[i][0].rgbtGreen;
	for (int i = 1; i < 800; i++) Sb[i][0] = Sb[i - 1][0] + arrbitmap[i][0].rgbtBlue;
	for (int i = 1; i < 600; i++) Sr[0][i] = Sr[0][i - 1] + arrbitmap[0][i].rgbtRed;
	for (int i = 1; i < 600; i++) Sg[0][i] = Sg[0][i - 1] + arrbitmap[0][i].rgbtGreen;
	for (int i = 1; i < 600; i++) Sb[0][i] = Sb[0][i - 1] + arrbitmap[0][i].rgbtBlue;
	for (int i = 1; i < 800; i++)
		for (int j = 1; j < 600; j++)
			Sr[i][j] = Sr[i - 1][j] + Sr[i][j - 1] - Sr[i - 1][j - 1] + arrbitmap[i][j].rgbtRed;
	for (int i = 1; i < 800; i++)
		for (int j = 1; j < 600; j++)
			Sg[i][j] = Sg[i - 1][j] + Sg[i][j - 1] - Sg[i - 1][j - 1] + arrbitmap[i][j].rgbtGreen;
	for (int i = 1; i < 800; i++)
		for (int j = 1; j < 600; j++)
			Sb[i][j] = Sb[i - 1][j] + Sb[i][j - 1] - Sb[i - 1][j - 1] + arrbitmap[i][j].rgbtBlue;
	beginPdot();
	ref(i, x, X)ref(j, y, Y) {
		int r, g, b, t;
		int p = 5;
		int s1, s2, s3, s4;
		s1 = Sr[min(i + p, w - 1)][min(j + p, h - 1)], s2 = ((j <= p) ? 0 : Sr[min(i + p, w - 1)][max(j - p, 0) - 1]);
		s3 = ((i <= p) ? 0 : Sr[max(i - p, 0) - 1][min(j + p, h - 1)]), s4 = ((i <= p || j <= p) ? 0 : Sr[max(i - p, 0) - 1][max(j - p, 0) - 1]);
		r = s1 - s2 - s3 + s4;
		s1 = Sg[min(i + p, w - 1)][min(j + p, h - 1)], s2 = ((j <= p) ? 0 : Sg[min(i + p, w - 1)][max(j - p, 0) - 1]);
		s3 = ((i <= p) ? 0 : Sg[max(i - p, 0) - 1][min(j + p, h - 1)]), s4 = ((i <= p || j <= p) ? 0 : Sg[max(i - p, 0) - 1][max(j - p, 0) - 1]);
		g = s1 - s2 - s3 + s4;
		s1 = Sb[min(i + p, w - 1)][min(j + p, h - 1)], s2 = ((j <= p) ? 0 : Sb[min(i + p, w - 1)][max(j - p, 0) - 1]);
		s3 = ((i <= p) ? 0 : Sb[max(i - p, 0) - 1][min(j + p, h - 1)]), s4 = ((i <= p || j <= p) ? 0 : Sb[max(i - p, 0) - 1][max(j - p, 0) - 1]);
		b = s1 - s2 - s3 + s4;
		t = (min(i + p, w - 1) - max(i - p, 0) + 1)*(min(j + p, w - 1) - max(j - p, 0) + 1);
		r /= t; g /= t; b /= t;
		Pdot(i, j, r, g, b);
	}
	endPdot();
}
void _restart() {
	flushmouse();
	Paintbmp(0, 0, _winw - 1, _winh - 1);
	beginPdot();
	double lightness = pi / 10;
	ref(i, 0, 600)ref(j, 200, 600) {
		COLORREF c = hsl2rgb(1.0*i / 600, 1.0*j / 600, lightness);
		Pdot(i + 40, j - 80, c);
	}
	endPdot();
	textbox t, trgb;
	t.init();
	t.text = "Choose a color for your character : ";
	t.setbox(40, 80, 640, 120);
	t.setstyle(BLACK, 30, 0, "微软雅黑", lgtop | lgleft);
	t.paint();

	button b1, b2, b3, b4, bnext;
	b1.init();
	b1.setstyle(GRAY170, BLACK, BLACK, GRAY150, GRAY140, GRAY120, 24, 0, "黑体");
	b2 = b3 = b4 = bnext = b1;
	b4.buttoncolor[0] = GRAY100;
	b1.setbox(660, 70, 760, 170);
	b2.setbox(660, 170, 760, 270);
	b3.setbox(660, 270, 760, 370);
	b4.setbox(660, 370, 760, 470);
	bnext.setbox(660, 480, 760, 530);
	bnext.text = "CONFIRM";
	picker p[3];
	p[0].init();
	p[0].setbox(40, 120, 640, 520);
	p[0].setstyle(5);
	p[1] = p[2] = p[0];
	flushpaint();
	trgb.init();
	trgb.setbox(t.tx2, 80, 640, 120);
	trgb.setstyle(BLACK, 30, 0, "微软雅黑", lgtop | lgleft);
	figureimage fg1, fg2, fg3, fg4;
	fg1.setposition((b1.x1 + b1.x2) / 2, (b1.y1 + b1.y2) / 2);
	fg2.setposition((b2.x1 + b2.x2) / 2, (b2.y1 + b2.y2) / 2);
	fg3.setposition((b3.x1 + b3.x2) / 2, (b3.y1 + b3.y2) / 2);
	fg4.setposition((b4.x1 + b4.x2) / 2, (b4.y1 + b4.y2) / 2);
	int current_p = 0;
	int cury = 70, idealy = 70;
	while (!_isquit) {
		peekmsg(); delay(3);
		b1.listen();
		b2.listen();
		b3.listen();
		if (p[0].picked&&p[1].picked&&p[2].picked) {
			bnext.textcolor[0] = BLACK;
			bnext.listen();
			if (bnext.lbuttonrelease) {
				fg4.angle = 0; figure = fg4;
				_restart1();
				return;
			}
		}
		if (b1.lbuttonrelease || b2.lbuttonrelease || b3.lbuttonrelease) {
			p[current_p].visibletrans();
			if (b1.lbuttonrelease)current_p = 0, idealy = 70; else
				if (b2.lbuttonrelease)current_p = 1, idealy = 170; else
					if (b3.lbuttonrelease)current_p = 2, idealy = 270;
			p[current_p].visibletrans();
			trgb.clear(GRAY200);
			if (p[current_p].picked) {
				COLORREF c = hsl2rgb(1.0*(p[current_p].x - 40) / 600, 1.0*(p[current_p].y + 80) / 600, lightness);
				trgb.textcolor = c;
				string text = "RGB( ";
				text = text + constr(GetRValue(c)) + ", " + constr(GetGValue(c)) + ", " + constr(GetBValue(c)) + ")";
				trgb.text = text.c_str();
				trgb.paint();
			}
		}
		p[current_p].listen();
		if (p[current_p].pickedtrans) {

			COLORREF c = hsl2rgb(1.0*(p[current_p].x - 40) / 600, 1.0*(p[current_p].y + 80) / 600, lightness);
			trgb.clear(GRAY200);
			trgb.textcolor = c;
			string text = "RGB( ";
			text = text + constr(GetRValue(c)) + ", " + constr(GetGValue(c)) + ", " + constr(GetBValue(c)) + ")";
			trgb.text = text.c_str();
			trgb.paint();

			if (current_p == 0) fg1.fc1 = fg4.fc1 = c; else
				if (current_p == 1) fg2.fc2 = fg4.fc2 = c; else
					if (current_p == 2) fg3.fc3 = fg4.fc3 = c;
		}
		b1.paint(); b2.paint(); b3.paint(); b4.paint(); bnext.paint();
		fg1.angle += 0.004;
		fg2.angle += 0.004;
		fg3.angle += 0.004;
		fg4.angle += 0.004;
		fg1.paint();
		fg2.paint();
		fg3.paint();
		fg4.paint();
		setd(0, 3, GRAY200); pline(655, cury, 655, cury + 100); pline(765, cury, 765, cury + 100);
		if (cury < idealy)cury += 3; if (cury > idealy)cury -= 3;
		setd(0, 3, BLACK); pline(655, cury, 655, cury + 100); pline(765, cury, 765, cury + 100);
		flushpaint();
	}
}
void _main() {
	textbox t, t1, t2, t3;
	t.init();
	t.text = "ALIVE";
	t.setbox(0, 0, _winw, _winh);
	t.setfont(60, 0, "Courtier New");
	t.layoutgravity = lgcenterhorizontal | lgcentervertical;
	ref(i, 50, 200) {
		clearscreen(rgb(i, i, i));
		t.textcolor = rgb(255 - i, 255 - i, 255 - i);
		t.paint();
		flushpaint();
		delay(5);
	}
	ref(i, 55, 200) {
		t.textcolor = rgb(i, i, i);
		t.paint();
		flushpaint();
		delay(10);
	}
	delay(100);

position1:
	flushmouse();
	clearscreen(GRAY200);
	paintbmp(0, 0, _winw-1,_winh-1);

	t1.init();
	t1.setstyle(GRAY100, 36, 15, "Courtier New", lgcenterhorizontal | lgcentervertical);
	t3 = t2 = t1;
	t1.text = "RESUME";
	t1.setbox(0, _winh * 8 / 12, _winw, _winh * 9 / 12);
	t1.paint();
	t2.text = "RESTART";
	t2.setbox(0, _winh * 9 / 12, _winw, _winh * 10 / 12);
	t2.paint();
	t3.text = "EXIT";
	t3.setbox(0, _winh * 10 / 12, _winw, _winh * 11 / 12);
	t3.paint();
	flushpaint();

	while (1) {
		t1.listen(); t2.listen(); t3.listen();
		if (t1.ifmouseovertranstrue()) {
			paintbmp(t1.tx1,t1.ty1,t1.tx2,t1.ty2);
			t1.textcolor = GRAY120; t1.fw = 16;
			t1.paint(); flushpaint();
		}
		else if (t1.ifmouseovertransfalse()) {
			paintbmp(t1.tx1, t1.ty1, t1.tx2, t1.ty2);
			t1.textcolor = GRAY100; t1.fw = 15;
			t1.paint(); flushpaint();
		}
		if (t2.ifmouseovertranstrue()) {
			paintbmp(t2.tx1, t2.ty1, t2.tx2, t2.ty2);
			t2.textcolor = GRAY120; t2.fw = 16;
			t2.paint(); flushpaint();
		}
		else if (t2.ifmouseovertransfalse()) {
			paintbmp(t2.tx1, t2.ty1, t2.tx2, t2.ty2);
			t2.textcolor = GRAY100; t2.fw = 15;
			t2.paint(); flushpaint();
		}
		if (t3.ifmouseovertranstrue()) {
			paintbmp(t3.tx1, t3.ty1, t3.tx2, t3.ty2);
			t3.textcolor = GRAY120; t3.fw = 16;
			t3.paint(); flushpaint();
		}
		else if (t3.ifmouseovertransfalse()) {
			paintbmp(t3.tx1, t3.ty1, t3.tx2, t3.ty2);
			t3.textcolor = GRAY100; t3.fw = 15;
			t3.paint(); flushpaint();
		}
		if (t1.lbuttonrelease) {
			_resume();
			goto position1;
		}
		if (t2.lbuttonrelease) {
			_restart();
			goto position1;
		}
		if (t3.lbuttonrelease) {
			return;
		}
		delay(1), peekmsg();
	}
}
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevinstance,
	LPSTR lpCmdline,
	int nCmdshow
) {
	if (checkprev("Alive"))return 0;
	initwin(hInstance, 800, 600, "Alive");
	showwin(nCmdshow);

	srand(time(0));

	_main();

	closewin(hwnd);
}