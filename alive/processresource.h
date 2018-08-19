#pragma once
#include "head.h"
struct intRGBTRIPLE {
	int r, g, b;
	intRGBTRIPLE() { r = g = b = 0; }
	intRGBTRIPLE(int R, int G, int B) { r = R, g = G, b = B; }
	intRGBTRIPLE(tagRGBTRIPLE s) { r = s.rgbtRed, g = s.rgbtGreen, b = s.rgbtBlue; }
	void operator =(tagRGBTRIPLE s) { r = s.rgbtRed; g = s.rgbtGreen; b = s.rgbtBlue; }
};
intRGBTRIPLE operator+(intRGBTRIPLE a, intRGBTRIPLE b) { return intRGBTRIPLE(a.r + b.r, a.g + b.g, a.b + b.b); }
intRGBTRIPLE operator+(intRGBTRIPLE a, tagRGBTRIPLE b) { return a + (intRGBTRIPLE)b; }
intRGBTRIPLE operator-(intRGBTRIPLE a, intRGBTRIPLE b) { return intRGBTRIPLE(a.r - b.r, a.g - b.g, a.b - b.b); }
intRGBTRIPLE operator-(intRGBTRIPLE a, tagRGBTRIPLE b) { return a - (intRGBTRIPLE)b; }
intRGBTRIPLE operator*(intRGBTRIPLE a, int b) { return intRGBTRIPLE(a.r * b, a.g * b, a.b * b); }
intRGBTRIPLE operator/(intRGBTRIPLE a, int b) { return intRGBTRIPLE(a.r / b, a.g / b, a.b / b); }

string UseCustomResource(int rcId, HINSTANCE hinst, BYTE* &rcData) {
	HRSRC hRsrc = FindResource(hinst, MAKEINTRESOURCE(rcId), RT_BITMAP);
	if (NULL == hRsrc) return "rcError1";
	DWORD dwSize = SizeofResource(hinst, hRsrc);
	if (0 == dwSize) return "rcError2";
	HGLOBAL hGlobal = LoadResource(hinst, hRsrc);
	if (NULL == hGlobal) return "rcError3";
	rcData = new BYTE[dwSize];
	ZeroMemory(rcData, sizeof(BYTE)*dwSize);
	CopyMemory(rcData, (PBYTE)LockResource(hGlobal), dwSize);
	return "";
}
void getarrbitmap(tagRGBTRIPLE arrbitmap[800][600], BYTE* rcData, int w, int h) {
	int cnt = 54;
	for (int j = h - 1; j >= 0; --j) {
		for (int i = 0; i < w; ++i) {
			BYTE r = rcData[cnt++], b = rcData[cnt++], g = rcData[cnt++];
			arrbitmap[i][j] = { b,g,r };
		}
		for (int i = 1; i <= (4 - w * 3 % 4) % 4; ++i)cnt++; 
	}
}