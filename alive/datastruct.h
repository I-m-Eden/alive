#pragma once
#ifndef H_DATASTRUCT
#define H_DATASTRUCT

#include "head.h"
#include "vector2.h"
template <class T> class lst {
public:
	lst<T> *L, *R; T s; bool isbegin, isend;
	lst<T>() { isbegin = 0; isend = 0; L = R = nullptr; }
};
template <class T> class linkst {
public:
	int sz;
	lst<T>* s;
	linkst<T>() { s = nullptr; sz = 0; }
	void clear() {
		while (s != nullptr) {
			lst<T>* t = s->R; delete s;
			s = t;
		}
	}
	void create() {
		clear();
		s = new lst<T>; s->isbegin = 1;
		s->R = new lst<T>; s->R->isend = 1;
		s->R->L = s;
		sz = 0;
	}
	lst<T>* insert(T t) {
		lst<T> *q = new lst<T>; q->s = t;
		q->R = s->R; q->L = s;
		s->R->L = q; s->R = q; sz++; return q;
	}
	void erase(lst<T>* S) {
		S->L->R = S->R;
		S->R->L = S->L; sz--;
		delete S;
	}
	void combine(linkst<T>* S) {
		for (lst<T>* it = S->begin(); !it->isend; it = it->R)
			insert(it->s);
	}
	lst<T>* begin() { return s->R; }
};
template <class T> class kdnode {
public:
	double x1, y1, x2, y2;
	bool dx, isend;
	linkst<T> s;
	kdnode<T> *L, *R;
	kdnode<T>() { x1 = y1 = x2 = y2 = 0; dx = 0; isend = 1; s.create(); L = R = nullptr; }
	kdnode<T>(double X1, double Y1, double X2, double Y2, bool Dx) { 
		x1 = X1, y1 = Y1, x2 = X2, y2 = Y2; dx = Dx; isend = 1;
		s.create(); L = R = nullptr;
	}
	lst<T>* additem(T a) { return s.insert(a); }
};
template <class T> class kdtree {
public:
	double x1, y1, x2, y2, px, py;
	kdnode<T> *s;
	void clear() { clear(s); }
	void create(double X1, double Y1, double X2, double Y2, double pctx=0.005, double pcty=0.005) {
		clear(); 
		x1 = X1, y1 = Y1, x2 = X2, y2 = Y2; px = (x2 - x1)*pctx; py = (y2 - y1)*pcty;
		s = new kdnode<T>(x1, y1, x2, y2, 0);
	}
	pair<kdnode<T>*, lst<T>*> insert(double x, double y, T a) {
		kdnode<T> *S = s;
		while (1) {
			if (S->x2 - S->x1 <= px && S->y2 - S->y1 <= py) { return make_pair(S,S->additem(a)); }
			if (S->isend) {
				S->isend = 0;
				if (S->dx) {
					bool Dx = (S->y2 - S->y1 <= py);
					S->L = new kdnode<T>(S->x1, S->y1, (S->x1 + S->x2) / 2, S->y2, Dx);
					S->R = new kdnode<T>((S->x1 + S->x2) / 2, S->y1, S->x2, S->y2, Dx);
				}
				else {
					bool Dx = !(S->x2 - S->x1 <= px);
					S->L = new kdnode<T>(S->x1, S->y1, S->x2, (S->y1 + S->y2) / 2, Dx);
					S->R = new kdnode<T>(S->x1, (S->y1 + S->y2) / 2, S->x2, S->y2, Dx);
				}
			}
			if (S->dx) { if (x <= S->L->x2)S = S->L; else S = S->R; }
			else { if (y <= S->L->y2)S = S->L; else S = S->R; }
		}
	}
	pair<kdnode<T>*, lst<T>*> insert(vector2 v, T a) { return insert(v.x, v.y, a); }
	void collectitem(linkst<T>* a, double x, double y, double r) {
		search(s, a, x, y, r);
	}
	void collectitem(linkst<T>* a, vector2 v, double r) {
		collectitem(a, v.x, v.y, r);
	}
private:
	void clear(kdnode<T>* &S) {
		if (S == nullptr)return;
		if (S->isend) { S->s.clear(); delete S; S = NULL; return; }
		clear(S->L); clear(S->R); S->s.clear(); delete S; S = NULL;
	}
	double getD(double x1, double y1, double x2, double y2, double x, double y) {
		if (x >= x1 && x <= x2 && y >= y1 && y <= y2)return 0;
		double dx = 0; if (x < x1)dx = x1 - x; else if (x > x2)dx = x - x2;
		double dy = 0; if (y < y1)dy = y1 - y; else if (y > y2)dy = y - y2;
		return dx*dx + dy*dy;
	}
	void search(kdnode<T>* S, linkst<T>* a, double x, double y, double r) {
		if (S == nullptr)return;
		if (getD(S->x1, S->y1, S->x2, S->y2, x, y) > r*r)return;
		if (S->isend) {
			a->combine(&S->s); return;
		}
		search(S->L, a, x, y, r);
		search(S->R, a, x, y, r);
	}
};

#endif