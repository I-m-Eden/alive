#pragma once
#ifndef H_DATASTRUCT
#define H_DATASTRUCT
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
	void create() {
		while (s != nullptr) {
			lst<T>* t = s->R; delete s;
			s = t;
		}
		s = new lst<T>; s->isbegin = 1;
		s->R = new lst<T>; s->R->isend = 1;
		sz = 0;
	}
	void insert(T t) {
		lst<T> *q = new lst<T>; q->s = t;
		q->R = s->R; q->L = s;
		s->R->L = q; s->R = q; sz++;
	}
	void erase(lst<T>* S) {
		S->L->R = S->R;
		S->R->L = S->L; sz--;
		delete S;
	}
	lst<T>* begin() { return s->R; }
};
#endif