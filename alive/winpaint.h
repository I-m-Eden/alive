#pragma once
#include <Windows.h>
#include <iostream>
#include <Vfw.h>
#include <cmath>
using namespace std;
#define rgb RGB
#define delay Sleep				//delay(x) �ӳ�x���� 

//��ܰ���ѣ�
//
//	ѭ������У�ÿ��peekmsg��������Ϣ�����������벻�������鷢��(#^.^#)��
//	ѭ������У�������Sleep(1)��delay(1)������cpuռ���ʣ����������������ᷢ��(#^.^#)��
//	�����WinMain�����������ĸ�����...
//	����ʼʱ������ȵ���initwin��showwin...
//	����ʼ����дbeginpaint,�������Ҳ����дendpaint
//	ÿ�λ�ͼ����������ڴ�DC�ϣ���û����ʾ����ʾ���ϡ���Ҫflushpaint()������ʾ����ʾ����
//	��ͷ�ļ�����ȫ�ֱ���hwnd�����ھ����_isquit�������Ƿ��˳���_winw,_winh�����ڵĿ�͸�
//	��ͷ�ļ�����ȫ�ֱ���_ms����ǰ��Ϣ(#^.^#)
//	������Ҫ���������ص��ʱ��ѡ��beginPdot��֮��ÿ�λ�����Pdot������������endPdot����ʾ����Ļ����flushpaint()��
//	��beginPdot��endPdot֮���κ�������ͼ��������Ч��ֻ��Pdot��Ч��ֻ�е�flushPdot��endPdot֮��Ż���Ƶ��ڴ�DC�ϡ�
//	������Ҫ���������ص��ʱ��ѡ��pdot��ԭ�򣺴����(#^.^#)

							//��ɫ����
const COLORREF WHITE = rgb(255, 255, 255);
const COLORREF BLACK = rgb(0, 0, 0);
const COLORREF GRAY = rgb(127, 127, 127);
const COLORREF RED = rgb(255, 0, 0);
const COLORREF GREEN = rgb(0, 255, 0);
const COLORREF BLUE = rgb(0, 0, 255);
const COLORREF YELLOW = rgb(255, 255, 0);
const COLORREF PURPLE = rgb(255, 0, 255);
const COLORREF CYAN = rgb(0, 255, 255);
const COLORREF ORANGE = rgb(255, 127, 0);
const HANDLE hnullbrush = GetStockObject(NULL_BRUSH);
								//�޻�ˢ
const HANDLE hnullpen = GetStockObject(NULL_PEN);
								//�޻���

							//���ڱ���
HWND hwnd;						//���ھ��
bool _isquit = 0;				//�����Ƿ��˳�
bool _isinit = 0;
int _winw = 0;					//���ڻ�ͼ����Ŀ�
int _winh = 0;					//���ڻ�ͼ����ĸ�
HINSTANCE _hinst;				//����ʵ�����
LPCSTR _title;					//���ڱ���

							//��Ϣ����
const int _msqmax = 10000;		
MSG _ms = { 0 };				//��ǰ��Ϣ
MSG _msq[_msqmax];				//��Ϣ����
MSG _msbuf[_msqmax];			//peekmsg��õ�����Ϣ��
int _msh=1, _mst=1, _msbufn=0;	

							//λͼ����
HDC _hdc;						//�豸��������
HDC _hDCMem;					//�ڴ�DC
int _w;							//λͼ�Ŀ�
int _h;							//λͼ�ĸ�
HBITMAP _hBMMem;				//λͼ���
HANDLE _hOld;					//��λͼ���
BITMAPINFO _bInfo;				//λͼ��Ϣ
int _nLnBytes;					//λͼÿ���ֽ���
BYTE* _pData;					//λͼ��ɫ��Ϣ
int _pDataSize;					//λͼ��ɫ��Ϣ����Ĵ�С

							//��ͼ����
COLORREF _tc;					//text��ɫ
HFONT _tfont;					//text����
HPEN _dpen;						//�������
HBRUSH _fbrush;					//�����



const int _thmax = 100;	
HANDLE _th[_thmax];				//�߳̾��
int _thi;						//�߳̾������

													//���ں���
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);				
														//�ص�����
ATOM MyRegisterClass(HINSTANCE hInstance);				//ע�ᴰ��
DWORD WINAPI _initwin(LPVOID lpParam);					//��ʼ�������̺߳���
void stopthread(int thi);								//ֹͣ�߳�
void newthread(LPTHREAD_START_ROUTINE t);				//�½��߳�
void initwin(HINSTANCE hInstance, int ww, int wh, LPCSTR title);
														//��ʼ�����ڣ�����ע�ᣬ�������ڣ�
void closewin(HWND hwnd);								//�رմ���
void showwin(int nCmdshow);								//��ʾ����
bool checkprev(LPCSTR wname);						//�ж��Ƿ�����ǰʵ��

													//��Ϣ����
void sendmsg(LPMSG ms);									//������Ϣ
bool peekmsg();											//����ȡ����Ϣ
bool iswndactive();										//�����Ƿ��ڼ���״̬
bool iskeydown();										//�Ƿ񰴼�
bool iskeydown(int x);									//�Ƿ񰴼�x
WPARAM getkeydown();										//��ȡ������Ϣ
bool islbuttondown();									//�Ƿ���������
bool islbuttonup();										//�Ƿ��ɿ�������
bool isrbuttondown();									//�Ƿ�������Ҽ�
bool isrbuttonup();										//�Ƿ��ɿ�����Ҽ�
bool iswheelrollup();									//�Ƿ���껬�����ϻ�
bool iswheelrolldown();									//�Ƿ���껬�����»�
bool ismousemove();										//����Ƿ��ƶ�

													//����λ�ú���
int getborderw();										//�õ����ڱ߿��
int getborderh();										//�õ����ڱ߿��
int getbordertitle();									//�õ����ڱ����
int getmouseabsx();										//�õ�����������x
int getmouseabsy();										//�õ�����������y
int getposx(HWND hwnd);									//�õ��������Ͻ�����x
int getposy(HWND hwnd);									//�õ��������Ͻ�����y
int getmousex(HWND hwnd);								//�õ�����ڻ�ͼ����������x
int getmousey(HWND hwnd);								//�õ�����ڻ�ͼ����������y
void setmousexy(int x, int y);							//��������ڻ�ͼ����������xy
void setmousexy(POINT p);								//��������ڻ�ͼ�����������

													//��ͼ����
void beginpaint(HWND hwnd, int W, int H);				//׼��˫��������ͼ
void flushpaint();										//����
void endpaint(HWND hwnd);								//��������
void beginPdot(bool flag);								//׼����ʼ�����ص�(flagΪ1������)
COLORREF Gdot(int x, int y);							//�õ����ص���ɫ(beginPdot��ʹ��)
void Gdot(int x, int y, BYTE&r, BYTE&g, BYTE&b);		//�õ����ص���ɫ(beginPdot��ʹ��)
void Pdot(int x, int y, BYTE r, BYTE g, BYTE b);		//���ٻ����ص�(beginPdot��ʹ��)
void Pdot(int x, int y, COLORREF c);					//���ٻ����ص�(beginPdot��ʹ��)
void flushPdot();										//�����ڴ�DC(beginPdot��ʹ��)
void endPdot();											//�����������ص�(beginPdot��ʹ��)
void rgb2hsl(COLORREF C, double &h, double &s, double &l);
														//rgbתhsl
COLORREF hsl2rgb(double h,double s,double l);			//hslתrgb
void inversehsl(double&h, double&s, double&l);			//��תhsl
COLORREF inversecolor(COLORREF c);						//��ת��ɫ
COLORREF inversergb(COLORREF c);						//��תrgb
COLORREF gdot(int x, int y);							//��ȡ������ɫ
void pdot(int x, int y, COLORREF c);					//�����ص�
void setd(int pstyle, int pwidth, COLORREF pc);			//�����������
void setf(COLORREF bc);									//���������ɫ
void setf(int bstyle, COLORREF bc);						//������������ɫ
void setf(HBITMAP hbm);									//�������ͼ��
void sett(COLORREF tc, int h, int w, LPCSTR lpf);		//����text��ɫ������
void dbar(int x1, int y1, int x2, int y2);				//���������
void dcircle(int x, int y, int r);						//��Բ���
void dellipse(int x1, int y1, int x2, int y2);			//����Բ���
void dpolygon(const POINT* apt, int cpt);				//����������
void dchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//���������
void dpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//���������
void droundbar(int x1, int y1, int x2, int y2, int w, int h);
														//��Բ�Ǿ������
void fbar(int x1, int y1, int x2, int y2);				//������
void fcircle(int x, int y, int r);						//���Բ
void fellipse(int x1, int y1, int x2, int y2);			//�����Բ
void fpolygon(const POINT* apt, int cpt);				//�������
void fchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//��乭��
void fpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//�������
void froundbar(int x1, int y1, int x2, int y2, int w, int h);
														//���Բ�Ǿ���
void pbar(int x1, int y1, int x2, int y2);				//��������򣬲�������
void pcircle(int x, int y, int r);						//��Բ��򣬲����Բ
void pellipse(int x1, int y1, int x2, int y2);			//����Բ��򣬲������Բ
void ppolygon(const POINT* apt, int cpt);				//���������򣬲��������
void pchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//�����Σ�����乭��
void ppie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//�����Σ����������
void proundbar(int x1, int y1, int x2, int y2, int w, int h);
														//��Բ�Ǿ��Σ������Բ�Ǿ���
void pline(int x1, int y1, int x2, int y2);				//����
void ptext(int x, int y, LPCSTR s);						//��text
void parc(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2);
														//����
void pbezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
														//������������
void clearscreen(int c, int x1, int y1, int x2, int y2);//�����Ļһ������
void clearscreen(int c);								//����

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	switch (uMsg) {
	case WM_DESTROY: { exit(0); break; }
	case WM_CREATE: { beginpaint(hwnd, _winw, _winh); break; }
	case WM_CLOSE: { closewin(hwnd); break; }
	case WM_PAINT: { flushpaint(); }
	}
	return DefWindowProc(hwnd, uMsg, wparam, lparam);
}
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "DefaultClassName";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	return RegisterClassEx(&wcex);
}
DWORD WINAPI _initwin(LPVOID lpParam) {
	if (!_isinit) {
		if (!MyRegisterClass(_hinst))
			MessageBox(NULL, "ע�ᴰ��ʧ��", "����", MB_OK);
		DWORD wsstyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
		RECT rect = { 0,0,_winw,_winh };
		AdjustWindowRectEx(&rect, wsstyle, 0, 0);
		hwnd = CreateWindowEx(
			NULL, "DefaultClassName", _title,
			wsstyle,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rect.right - rect.left, rect.bottom - rect.top,
			NULL, NULL, _hinst, NULL
		);
		if (!hwnd) MessageBox(NULL, "��������ʧ��", "����", MB_OK);
		_isinit = 1;
	}
	while (!_isquit) {
		MSG msg = { 0 };
		GetMessage(&msg, hwnd, 0, 0);
		sendmsg(&msg);
		_msq[_mst] = msg;
		_mst++; if (_mst >= _msqmax)_mst = 0;
	}
	return 0;
}
void stopthread(int thi) {
	TerminateThread(_th[thi], 0);
}
void newthread(LPTHREAD_START_ROUTINE t) {
	DWORD _tmp;
	_thi++;
	_thi=_thi % _thmax;
	stopthread(_thi);
	_th[_thi] = CreateThread(NULL, 0, t, NULL, 0, &_tmp);
}
void initwin(HINSTANCE hInstance, int ww,int wh,LPCSTR title) {
	_winw = ww; _winh = wh;
	_hinst = hInstance;
	_title = title;
	newthread(&_initwin);
	while (!_isinit)delay(1);
}
void closewin(HWND hwnd) { endpaint(hwnd); DestroyWindow(hwnd); _isquit = 1; }
void showwin(int nCmdshow) { ShowWindow(hwnd, nCmdshow); UpdateWindow(hwnd); }
bool checkprev(LPCSTR wname) { if (FindWindow("DefaultClassName",wname)) { MessageBox(NULL, "Ӧ�ó�����������", "ע��", MB_OK); return 1;  } else return 0;}
void sendmsg(LPMSG lpms) { TranslateMessage(lpms); DispatchMessage(lpms); }
bool peekmsg() {
	_msbufn = 0;
	if (_msh != _mst) {
		while (1) {
			_msbuf[++_msbufn] = _ms = _msq[_msh];
			_msh++; if (_msh >= _msqmax)_msh = 0;
			if ((_mst - _msh + _msqmax) % _msqmax <= 10)break;
		}
		return 1;
	}
	return 0;
}
bool iswndactive() {
	return GetForegroundWindow() == hwnd;
}
bool iskeydown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_KEYDOWN)return 1;
	return 0;
}
bool iskeydown(int x) {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_KEYDOWN && _msbuf[i].wParam == x)return 1;
	return 0;
}
WPARAM getkeydown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_KEYDOWN)return _msbuf[i].wParam;
	return 0;
}
bool islbuttondown() { 
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_LBUTTONDOWN)return 1;
	return 0;
}
bool islbuttonup() {

	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_LBUTTONUP)return 1;
	return 0;
}
bool isrbuttondown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_RBUTTONDOWN)return 1;
	return 0;
}
bool isrbuttonup() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_RBUTTONUP)return 1;
	return 0;
}
bool iswheelrollup() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_MOUSEWHEEL && (HIWORD(_msbuf[i].wParam) == 120))return 1;
	return 0;
}
bool iswheelrolldown() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_MOUSEWHEEL && (HIWORD(_msbuf[i].wParam) == (WORD)-120))return 1;
	return 0;
}
bool ismousemove() {
	for (int i = 1; i <= _msbufn; ++i)if (_msbuf[i].message == WM_MOUSEMOVE)return 1;
	return 0;
}
int getborderw() { return GetSystemMetrics(SM_CXFRAME); }
int getborderh() { return GetSystemMetrics(SM_CYFRAME); }
int getbordertitle() { return GetSystemMetrics(SM_CYCAPTION); }
int getmouseabsx() { POINT p; GetCursorPos(&p);return p.x; }
int getmouseabsy() { POINT p; GetCursorPos(&p);return p.y; }
int getposx(HWND hwnd) { RECT r; GetWindowRect(hwnd, &r); return r.left; }
int getposy(HWND hwnd) { RECT r; GetWindowRect(hwnd, &r); return r.top; }
int getmousex(HWND hwnd) { return getmouseabsx() - getposx(hwnd) - getborderw() * 2; }
int getmousey(HWND hwnd) { return getmouseabsy() - getposy(hwnd) - getborderh() * 2 - getbordertitle(); }
void setmousexy(int x, int y) { SetCursorPos(x + getposx(hwnd) + getborderw() * 2, y + getposy(hwnd) + getborderh() * 2 + getbordertitle()); }
void setmousexy(POINT p) { setmousexy(p.x, p.y); }
void beginpaint(HWND hwnd, int W,int H) {
	_w = W; _h = H;
	_hdc = GetDC(hwnd);
	_hDCMem = CreateCompatibleDC(_hdc);
	_hBMMem = CreateCompatibleBitmap(_hdc, W, H);
	_hOld = SelectObject(_hDCMem, _hBMMem);
	SetBkMode(_hDCMem, TRANSPARENT);
}
void flushpaint() {
	BitBlt(_hdc, 0, 0, _w, _h, _hDCMem, 0, 0, SRCCOPY);
}
void endpaint(HWND hwnd){
	flushpaint();
	SelectObject(_hDCMem, _hOld);
	DeleteObject(_hBMMem);
	DeleteDC(_hDCMem);
	ReleaseDC(hwnd, _hdc);
}
void beginPdot(bool flag = 0) {
	_bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_bInfo.bmiHeader.biWidth = _winw;
	_bInfo.bmiHeader.biHeight = _winh;
	_bInfo.bmiHeader.biPlanes = 1;
	_bInfo.bmiHeader.biBitCount = 24;
	_bInfo.bmiHeader.biCompression = BI_RGB;
	_bInfo.bmiHeader.biXPelsPerMeter = 0;
	_bInfo.bmiHeader.biYPelsPerMeter = 0;
	_bInfo.bmiHeader.biClrUsed = 0;
	_bInfo.bmiHeader.biClrImportant = 0;
	_nLnBytes = (_bInfo.bmiHeader.biWidth * 3 + 3) / 4 * 4;
	_pDataSize = _nLnBytes * _bInfo.bmiHeader.biHeight;
	_pData = new BYTE[_pDataSize];
	if (flag) memset(_pData, 0, _nLnBytes*abs(_bInfo.bmiHeader.biHeight)); 
	else GetDIBits(_hDCMem, _hBMMem, 0, _bInfo.bmiHeader.biHeight, _pData, &_bInfo, DIB_RGB_COLORS);
}
COLORREF Gdot(int x, int y) {
	if (x < 0 || x >= _winw || y < 0 || y >= _winh)return NULL;
	int t = (_winh - 1 - y) * _nLnBytes + x * 3;
	return (*(_pData + t + 2) | (*(_pData + t + 1) << 8) | (*(_pData + t + 0) << 16));
}
void Gdot(int x, int y, BYTE&r, BYTE&g, BYTE&b) {
	if (x < 0 || x >= _winw || y < 0 || y >= _winh)return;
	int t = (_winh - 1 - y) * _nLnBytes + x * 3;
	r = *(_pData + t + 2); g = *(_pData + t + 1); b = *(_pData + t + 0);
}
void Pdot(int x, int y, BYTE r, BYTE g, BYTE b) {
	if (x < 0 || x >= _winw || y < 0 || y >= _winh)return;
	int t = (_winh - 1 - y) * _nLnBytes + x * 3;
	*(_pData + t + 0) = b;
	*(_pData + t + 1) = g;
	*(_pData + t + 2) = r;
}
void Pdot(int x, int y, COLORREF c) {
	if (x < 0 || x >= _winw || y < 0 || y >= _winh)return;
	int t = (_winh - 1 - y) * _nLnBytes + x * 3;
	*(_pData + t + 0) = c >> 16 & 0xff;
	*(_pData + t + 1) = c >> 8 & 0xff;
	*(_pData + t + 2) = c >> 0 & 0xff;
}
void flushPdot() { SetDIBits(_hDCMem, _hBMMem, 0, _bInfo.bmiHeader.biHeight, _pData, &_bInfo, DIB_RGB_COLORS); }
void endPdot() { flushPdot(); delete[]_pData; }
COLORREF gdot(int x, int y) { return GetPixel(_hDCMem, x, y); }
COLORREF inversergb(COLORREF c) { return 0xffffff-c; }
void inversehsl(double&h, double&s, double&l) { h += 0.5; s += 0.5; l += 0.5; if (h >= 1)h -= 1; if (s >= 1)s -= 1; if (l >= 1)l -= 1; }
COLORREF inversecolor(COLORREF c) {
	double h, s, l; rgb2hsl(c, h, s, l);
	inversehsl(h, s, l); return hsl2rgb(h, s, l);
}
void pdot(int x, int y, COLORREF c) { SetPixel(_hDCMem, x, y, c); }
void rgb2hsl(COLORREF C, double &h, double &s, double &l) {
	double r, g, b, m, mm, c;
	r = 1.0*GetRValue(C) / 255.0; g = 1.0*GetGValue(C) / 255.0; b = 1.0*GetBValue(C) / 255.0;
	m = max(max(r, g), b); mm = min(min(r, g), b); c = m - mm;
	if (c == 0)h = 0; else
		if (m == r)h = (g - b) / c / 6; else
			if (m == g)h = (b - r) / c / 6 + 1.0 / 3; else
				if (m == b)h = (r - g) / c / 6 + 2.0 / 3;
	if (h < 0)h += 1;
	l = (m + mm) / 2;
	if (l == 1)s = 0; else s = c / (1 - fabs(2.0 * l - 1));
}
COLORREF hsl2rgb(double h, double s, double l) {
	double c, x,r,g,b;
	c = (1.0 - fabs(l * 2 - 1))*s;
	x = h * 6; while (x >= 2)x -= 2;
	x = c * (1 - fabs(x - 1));
	if (0.0 / 6 <= h && h <= 1.0 / 6)r = c, g = x, b = 0;
	if (1.0 / 6 <= h && h <= 2.0 / 6)r = x, g = c, b = 0;
	if (2.0 / 6 <= h && h <= 3.0 / 6)r = 0, g = c, b = x;
	if (3.0 / 6 <= h && h <= 4.0 / 6)r = 0, g = x, b = c;
	if (4.0 / 6 <= h && h <= 5.0 / 6)r = x, g = 0, b = c;
	if (5.0 / 6 <= h && h <= 6.0 / 6)r = c, g = 0, b = x;
	r = r + l - c / 2; r = r * 255.0;
	g = g + l - c / 2; g = g * 255.0;
	b = b + l - c / 2; b = b * 255.0;
	return RGB((int)round(r), (int)round(g), (int)round(b));
}
void pline(int x1, int y1, int x2, int y2) { MoveToEx(_hDCMem, x1, y1, NULL); LineTo(_hDCMem, x2, y2); }
void setd(int pstyle, int pwidth, COLORREF pc) {
	DeleteObject(_dpen);
	_dpen=CreatePen(pstyle, pwidth, pc);
	SelectObject(_hDCMem, _dpen);
}
void setf(COLORREF bc) {
	DeleteObject(_fbrush);
	_fbrush = CreateSolidBrush(bc);
	SelectObject(_hDCMem, _fbrush);
}
void setf(int bstyle, COLORREF bc) {
	DeleteObject(_fbrush);
	if (bstyle==-1) _fbrush = CreateSolidBrush(bc);
	else _fbrush = CreateHatchBrush(bstyle, bc);
	SelectObject(_hDCMem, _fbrush);
}
void setf(HBITMAP hbm) {
	DeleteObject(_fbrush);
	_fbrush = CreatePatternBrush(hbm);
	SelectObject(_hDCMem, _fbrush);
}
void sett(COLORREF tc, int h, int w, LPCSTR lpf) {
	SetTextColor(_hDCMem, _tc = tc);
	DeleteObject(_tfont);
	HFONT hfont = CreateFont(h, w, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, lpf);
	SelectObject(_hDCMem, _tfont = hfont);
}
void dbar(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullbrush);
	Rectangle(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _fbrush);
}
void fbar(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullpen);
	Rectangle(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _dpen);
}
void pbar(int x1, int y1, int x2, int y2) { Rectangle(_hDCMem, x1, y1, x2, y2); }
void clearscreen(int c, int x1, int y1, int x2, int y2) {
	HBRUSH hbrush = CreateSolidBrush(c);
	SelectObject(_hDCMem, hbrush);
	SelectObject(_hDCMem, hnullpen);
	Rectangle(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _fbrush);
	SelectObject(_hDCMem, _dpen);
	DeleteObject(hbrush);
}
void clearscreen(int c) {
	clearscreen(c, 0, 0, _winw+1, _winh+1);
}
void dcircle(int x, int y, int r) {
	SelectObject(_hDCMem, hnullbrush);
	Ellipse(_hDCMem, x - r, y - r, x + r, y + r);
	SelectObject(_hDCMem, _fbrush);
}
void fcircle(int x, int y, int r) {
	SelectObject(_hDCMem, hnullpen);
	Ellipse(_hDCMem, x - r, y - r, x + r, y + r);
	SelectObject(_hDCMem, _dpen);
}
void pcircle(int x, int y, int r) { Ellipse(_hDCMem, x - r, y - r, x + r, y + r); }
void dellipse(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullbrush);
	Ellipse(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _fbrush);
}
void fellipse(int x1, int y1, int x2, int y2) {
	SelectObject(_hDCMem, hnullpen);
	Ellipse(_hDCMem, x1, y1, x2, y2);
	SelectObject(_hDCMem, _dpen);
}
void pellipse(int x1, int y1, int x2, int y2) { Ellipse(_hDCMem, x1, y1, x2, y2); }
void dpolygon(const POINT* apt, int cpt) {
	SelectObject(_hDCMem, hnullbrush);
	Polygon(_hDCMem, apt, cpt);
	SelectObject(_hDCMem, _fbrush);
}
void fpolygon(const POINT* apt, int cpt) {
	SelectObject(_hDCMem, hnullpen);
	Polygon(_hDCMem, apt, cpt);
	SelectObject(_hDCMem, _dpen);
}
void ppolygon(const POINT* apt, int cpt) { Polygon(_hDCMem, apt, cpt); }
void parc(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	Arc(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
}
void dchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullbrush);
	Chord(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _fbrush);
}
void fchord(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullpen);
	Chord(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _dpen);
}
void pchord(int x1,int y1,int x2,int y2,int xx1,int yy1,int xx2,int yy2) {
	Chord(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
}
void dpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullbrush);
	Pie(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _fbrush);
}
void fpie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	SelectObject(_hDCMem, hnullpen);
	Pie(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
	SelectObject(_hDCMem, _dpen);
}
void ppie(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2) {
	Pie(_hDCMem, x1, y1, x2, y2, xx1, yy1, xx2, yy2);
}
void droundbar(int x1, int y1, int x2, int y2, int w, int h) {
	SelectObject(_hDCMem, hnullbrush);
	RoundRect(_hDCMem, x1, y1, x2, y2, w, h);
	SelectObject(_hDCMem, _fbrush);
}
void froundbar(int x1, int y1, int x2, int y2, int w, int h) {
	SelectObject(_hDCMem, hnullpen);
	RoundRect(_hDCMem, x1, y1, x2, y2, w, h);
	SelectObject(_hDCMem, _dpen);
}
void proundbar(int x1, int y1, int x2, int y2, int w, int h) {
	RoundRect(_hDCMem, x1, y1, x2, y2, w, h);
}
void ptext(int x, int y, LPCSTR s) { TextOut(_hDCMem, x, y, s, (int)strlen(s)); }
void pbezier(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4) {
	POINT pt[] = { {x1,y1},{x2,y2},{x3,y3},{x4,y4} };
	PolyBezier(_hDCMem, pt, 4);
}