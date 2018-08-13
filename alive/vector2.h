#pragma once
#ifndef H_VECTOR2
#define H_VECTOR2

#include "head.h"
struct vector2 {
	double x, y;
	vector2() { x = 0; y = 0; }
	vector2(double X, double Y) { x = X; y = Y; }
};
double norm(vector2 p) {
	return sqrt(p.x*p.x + p.y*p.y);
}
vector2 operator+(vector2 a, vector2 b) {
	return vector2(a.x + b.x, a.y + b.y);
}
vector2 operator-(vector2 a, vector2 b) {
	return vector2(a.x - b.x, a.y - b.y);
}
vector2 operator*(vector2 a, double s) {
	return vector2(a.x*s, a.y*s);
}
double operator*(vector2 a, vector2 b) {
	return a.x*b.x + a.y*b.y;
}
double operator^(vector2 a, vector2 b) { 
	return a.x*b.y - a.y*b.x; 
}
bool operator ==(vector2 a, vector2 b) {
	return a.x == b.x&&a.y == b.y;
}
double atan2(vector2 a) {
	return atan2(a.y, a.x);
}
#endif