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
//	_CRT_NONSTDC_NO_DEPRECATEaa
//	项目属性->c/c++->代码生成->运行库 修改为 "多线程调试 (/MTd)"
//

#define DEBUGGING

#include "head.h"
#include "vector2.h"
#include "datastruct.h"
#include "resource.h"
#include "winpaint.h"
#include "toolibrary.h"
#include "coloresource.h"
#include "imageresource.h"
#include "processresource.h"
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
void flushmouse() { while (GetAsyncKeyState(VK_LBUTTON)&0x8000)delay(1); while (peekmsg())delay(1); }
void flushkey() { FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); }

class enemyinf {
public:
	int ID;
	double ang;
	double life;
	int tmp;
	enemyinf() { ID = -1; ang = 0; life = 0; tmp = 0; }
	enemyinf(int _id, double _ang, double _life) { ID = _id; ang = _ang; life = _life; tmp = 0; }
	enemyinf(int _id, double _ang) {
		ID = _id;
		ang = _ang;
		life = getenemylife(ID);
		tmp = 0;
	}
	enemyinf(int _id) {
		ID = _id;
		ang = 1.0*(rand() % 628) / 100;
		life = getenemylife(ID);
		tmp = 0;
	}
};
typedef pair<vector2, int> pvi; 
typedef pair<vector2, double> pvd;
typedef pair<vector2, vector2> pvv;
typedef pair<vector2, enemyinf> pve;
typedef lst<pvi>* p_pvi;
typedef lst<pvd>* p_pvd;
typedef lst<pve>* p_pve;
typedef lst<pvv>* p_pvv;
typedef lst<p_pvi>* p_ppvi;
typedef lst<p_pvd>* p_ppvd;
typedef lst<p_pve>* p_ppve;
typedef lst<p_pvv>* p_ppvv;
typedef lst<int>* p_i;

int mx1, my1, mx2, my2;
figureimage figure;
vector2 realp, realv;
linkst<pvi> mp;
linkst<pve> mpenemy;
linkst<pvv> mpbullet;
int number_wood, number_stone;
double velocity, velocityenemy1, velocityenemy2, velocityenemy3, velocityenemy4;
double velocitybullet, velocityreload, velocityexploit; int multipleshoot;
double rangebullet;
double mist; int Ntree, Nstone, Nenemy1, Nenemy2, Nenemy3, Nenemy4;
const int SHOPN = 20;
bool shoppossession[SHOPN];
double HP, FP;
int currenttick;

linkst<p_pvi> mpobj, mptch;
p_pvi gainobj; double gainpct;
kdtree<p_pvi> mpkd;
map<p_pvi, pair<kdnode<p_pvi>*,p_ppvi> > kdpos;

linkst<p_pve> mpeobj, mpetch;

void initgame();
void loadgame();
void savegame();
bool sighted(vector2 p, int name);
void producemap();
vector2 randomposition(int name);
void produceobj(int name);
void paintgaining(p_pvi obj, double pct);
void paintmap();
void paintmist(double p);
void updatebullet();
void adjust(vector2 rp, double range, vector2&v, linkst<p_pvi>* S);
void makeenemy1route(pve&s);
void makeenemy2route(pve&s);
void makeenemy3route(pve&s);
void makeenemy4route(pve&s);
void updateenemy();
void updatekilled();
void updatefruit();
void getsighted();
void getsightedenemy();
void clearsighted();
void gettouch();
void gettouchenemy();
void eraseall(p_pvi it);
void eraseallenemy();
void updateQ(bool isQ);
bool updatetouchenemy();
void updateeatfruit();
void initkdtree();

namespace ns_shop {
	struct shopitem {
		string name, description; double valuechange;
		int comsumewood, comsumestone; linkst<int> from;
	}shop[SHOPN]; int shopn;
	BYTE* pData;
	void freshbackground() {
		beginPdot(true);
		memcpy(_pData, pData, _pDataSize);
		endPdot();
	}
	bool _gainshop(int id) {
		if (number_wood >= shop[id].comsumewood && number_stone >= shop[id].comsumestone) {
			number_wood -= shop[id].comsumewood;
			number_stone -= shop[id].comsumestone;
			if (shop[id].name == "velocity") velocity += shop[id].valuechange;
			if (shop[id].name == "multipleshoot") multipleshoot += (int)round(shop[id].valuechange);
			if (shop[id].name == "velocitybullet") velocitybullet += shop[id].valuechange;
			if (shop[id].name == "velocityexploit") velocityexploit += shop[id].valuechange;
			if (shop[id].name == "velocityreload") velocityreload += shop[id].valuechange;
			if (shop[id].name == "rangebullet") rangebullet += shop[id].valuechange;
			return 1;
		}
		else {
			textbox tb;tb.init();
			tb.setbox(0, _winh - 50, _winw, _winh);
			tb.setstyle(RED, 30, 0, "", lgcenterhorizontal | lgtop);
			tb.text = "You don't have enough material!";
			tb.paint(); flushpaint();
			delay(600);
			freshbackground(); flushpaint();
			return 0;
		}
	}
	void _freshshop(linkst<pair<int, button> >* S) {
		freshbackground();

		textbox tb; button bt;
		tb.init();
		tb.setstyle(GRAY80, 30, 0, "", lgleft | lgcentervertical);
		bt.init();
		bt.setstyle(GRAY100, GRAY100, GRAY100, GRAY200, GRAY180, GRAY150, 30, 0, "");

		S->create();
		int pos = 50;
		ref(i, 0, shopn - 1) if (!shoppossession[i]) {
			bool flag = 1;
			for (p_i j = shop[i].from.begin(); !j->isend; j = j->R)
				flag = flag && shoppossession[j->s];
			if (flag) {
				bool fg1 = shop[i].comsumewood <= number_wood;
				bool fg2 = shop[i].comsumestone <= number_stone;
				tb.setbox(50, pos, _winw, pos + 50);
				tb.text = shop[i].description.c_str(); tb.textcolor = (fg1&&fg2) ? BLUE : GRAY100;
				tb.paint();
				tb.setbox(300, pos, _winw, pos + 50);
				string s = constr(shop[i].comsumewood); s = "Wood × " + s;
				tb.text = s.c_str(); tb.textcolor = fg1 ? BLUE : GRAY100;
				tb.paint();
				tb.setbox(500, pos, _winw, pos + 50);
				s = constr(shop[i].comsumestone); s = "Stone × " + s;
				tb.text = s.c_str(); tb.textcolor = fg2 ? BLUE : GRAY100;
				tb.paint();
				bt.text = "BUY";
				bt.setbox(650, pos + 10, 750, pos + 40);
				bt.paint();
				pos += 50;
				S->insert(make_pair(i, bt));
			}
		}
	}
	void _inputshopdata() {
		ifstream fin("shop.txt");
		fin >> shopn;
		ref(i, 0, shopn - 1) {
			fin >> shop[i].name; ref(times, 0, 1) getline(fin, shop[i].description);
			fin >> shop[i].valuechange >> shop[i].comsumewood >> shop[i].comsumestone;
			int m, to; fin >> m; shop[i].from.create();
			ref(j, 1, m) { fin >> to; shop[i].from.insert(to); }
		}
		fin.close();
	}
	void _shop() {
		pData = new BYTE[_pDataSize];
		flushmouse();
		beginPdot();
		for (int i = 0; i < _pDataSize; ++i)
			_pData[i] = (BYTE)round(_pData[i] * 0.1 + 255 * 0.9);
		memcpy(pData, _pData, _pDataSize);
		endPdot();
		flushpaint();
		_inputshopdata();
		linkst<pair<int, button> >*S = new linkst<pair<int, button> >;
		_freshshop(S);
		while (!_isquit) {
			peekmsg(); delay(1);
			if (iskeydown(VK_ESCAPE))break;
			for (lst<pair<int, button> >* i = S->begin(); !i->isend; i = i->R) {
				i->s.second.listen();
				if (i->s.second.lbuttonrelease) {
					if (_gainshop(i->s.first))
						shoppossession[i->s.first] = 1;
					_freshshop(S);
					break;
				}
			}
			flushpaint();
		}
		ref(i, 0, shopn - 1)shop[i].from.clear();
		S->clear(); delete S;
		delete[] pData;
	}
};

void initgame() {
	figure.setposition(_winw / 2, _winh / 2);
	figure.angle = 0;
	mx1 = -3000; my1 = -3000; mx2 = 3000; my2 = 3000;
	producemap();
	realp = { 0,0 }; realv = { 0,0 };
	number_wood = 0, number_stone = 0;
	velocity = 2.5; velocityenemy1 = 1.7; velocityenemy2 = 2.7; velocityenemy3 = 6.0;  velocityenemy4 = 6.0;
	velocitybullet = 5; velocityreload = 50; velocityexploit = 1.0 / 120; multipleshoot = 1;
	rangebullet = 300.0;
	mist = 0.0;
	HP = 100.0; FP = 100.0;
	memset(shoppossession, 0, sizeof shoppossession);
	shoppossession[0] = 1;
	currenttick = 0;
#ifdef DEBUGGING
	HP = 100000.0;
	number_stone = 1000;
	number_wood = 1000;
#endif
}

void loadgame()
{
	ifstream fin("user.dat");
	figure = figuredemo;
	figure.setposition(_winw / 2, _winh / 2);
	fin >> mx1 >> mx2 >> my1 >> my2;
	fin >> figure.fc1 >> figure.fc2 >> figure.fc3;
	int n, x; double a, b, c, d;
	fin >> figure.r1 >> realp.x >> realp.y >> realv.x >> realv.y >> n;
	mp.create(); mpenemy.create(); mpbullet.create();
	ref(i, 1, n) {
		fin >> a >> b >> x;
		mp.insert(make_pair(vector2(a, b), x));
	}
	fin >> n;
	ref(i, 1, n) {
		enemyinf e; fin >> a >> b >> e.ID >> e.ang >> e.life;
		mpenemy.insert(make_pair(vector2(a, b), e));
	}
	fin >> n;
	ref(i, 1, n) {
		fin >> a >> b >> c >> d;
		mpbullet.insert(make_pair(vector2(a, b), vector2(c, d)));
	}
	fin >> number_wood >> number_stone;
	fin >> velocity >> velocityenemy1 >> velocityenemy2 >> velocityenemy3 >> velocityenemy4 >>
		velocitybullet >> velocityreload >> velocityexploit >> multipleshoot;
	fin >> rangebullet;
	fin >> mist >> Ntree >> Nstone >> Nenemy1 >> Nenemy2 >> Nenemy3 >> Nenemy4 >> HP >> FP;
	fin >> n;
	ref(i, 0, n - 1) fin>>shoppossession[i];
	fin >> currenttick;
	fin.close();
}

void savegame()
{
	ofstream fout("user.dat");
	fout.precision(6);
	fout << mx1 << " " << mx2 << " " << my1 << " " << my2 << endl;
	fout << figure.fc1 << " " << figure.fc2 << " " << figure.fc3 << endl;
	fout << figure.r1 << endl;
	fout << realp.x << " "<<realp.y << " "<<realv.x << " "<<realv.y << endl;
	fout << mp.sz << endl;
	for (p_pvi it = mp.s->R; !it->isend; it = it->R)
		fout << (*it).s.first.x << " " << (*it).s.first.y << " " << (*it).s.second << endl;
	fout << mpenemy.sz << endl;
	for (p_pve it = mpenemy.s->R; !it->isend; it = it->R)
		fout << (*it).s.first.x << " " << (*it).s.first.y << " " << 
			(*it).s.second.ID << " "<<(*it).s.second.ang<<" "<<(*it).s.second.life<< endl;
	fout << mpbullet.sz << endl;
	for (p_pvv it = mpbullet.s->R; !it->isend; it = it->R)
		fout << (*it).s.first.x << " " << (*it).s.first.y << " " << (*it).s.second.x << " " << (*it).s.second.y << endl;
	fout << number_wood << " " << number_stone << endl;
	fout << velocity << " " << velocityenemy1 << " " << velocityenemy2 << " " << velocityenemy3 << " " << velocityenemy4 << " " <<
		velocitybullet << " " << velocityreload << " " << " " << velocityexploit << " " << multipleshoot << endl;
	fout << rangebullet << endl;
	fout << mist << " " << Ntree << " " << Nstone << endl
		<< Nenemy1 << " " << Nenemy2 << " " << Nenemy3 << " " << Nenemy4 << endl
		<< HP << " " << FP << endl;
	fout << ns_shop::shopn << endl;
	ref(i, 0, ns_shop::shopn - 1)fout << (int)shoppossession[i] << " ";
	fout << endl;
	fout << currenttick << endl;
	fout.close();
}

bool sighted(vector2 p, int name) {
	if (name == IDTREE) return (p.x >= -treedemo.r&&p.x <= _winw + treedemo.r&&p.y >= -treedemo.r&&p.y <= _winh + treedemo.r);
	if (name == IDSTONE) return (p.x >= -stonedemo.r&&p.x <= _winw + stonedemo.r&&p.y >= -stonedemo.r&&p.y <= _winh + stonedemo.r);
	if (name == IDFRUIT) return (p.x >= -fruitdemo.r&&p.x <= _winw + fruitdemo.r&&p.y >= -fruitdemo.r&&p.y <= _winh + fruitdemo.r);
	if (name == IDENEMY1) return (p.x >= -enemy1demo.rw&&p.x <= _winw + enemy1demo.rw&&p.y >= -enemy1demo.rh&&p.y <= _winh + enemy1demo.rh);
	if (name == IDENEMY2) return (p.x >= -enemy2demo.rw&&p.x <= _winw + enemy2demo.rw&&p.y >= -enemy2demo.rh&&p.y <= _winh + enemy2demo.rh);
	if (name == IDENEMY3) return (p.x >= -enemy3demo.rw&&p.x <= _winw + enemy3demo.rw&&p.y >= -enemy3demo.rh&&p.y <= _winh + enemy3demo.rh);
	if (name == IDENEMY4) return (p.x >= -enemy4demo.r&&p.x <= _winw + enemy4demo.r&&p.y >= -enemy4demo.r&&p.y <= _winh + enemy4demo.r);
}
vector2 randompos() {
	return vector2(rand() % (mx2 - mx1) + mx1, rand() % (my2 - my1) + my1);
}
void producemap() {
	mp.create(); mpenemy.create(); mpbullet.create();
	Ntree = 250; Nstone = 500; Nenemy1 = 3; Nenemy2 = 5; Nenemy3 = 0; Nenemy4 = 3;
#ifdef DEBUGGING
	Nenemy1 = 30;
	Nenemy2 = 50;
	Nenemy3 = 40;
	Nenemy4 = 30;
#endif
	ref(i, 1, Ntree)mp.insert(make_pair(randompos(), IDTREE));
	ref(i, 1, Nstone)mp.insert(make_pair(randompos(), IDSTONE));
	ref(i, 1, Nenemy1)mpenemy.insert(make_pair(randompos(), enemyinf(IDENEMY1)));
	ref(i, 1, Nenemy2)mpenemy.insert(make_pair(randompos(), enemyinf(IDENEMY2)));
	ref(i, 1, Nenemy4)mpenemy.insert(make_pair(randompos(), enemyinf(IDENEMY4)));
}
void declineN(int id) {
	if (id == IDTREE) Ntree--;
	if (id == IDSTONE)Nstone--;
	if (id == IDENEMY1)Nenemy1--;
	if (id == IDENEMY2)Nenemy2--;
	if (id == IDENEMY3)Nenemy3--;
	if (id == IDENEMY4)Nenemy4--;
}
vector2 randomposition(int name) {
	while (1) {
		vector2 p = randompos();
		if (!sighted(p - realp + vector2(_winw/2, _winh/2), name))return p;
	}
}
void produceobj(int name) {
	vector2 p = randomposition(name);
	if (name == IDTREE || name == IDSTONE) 
		mpkd.insert(p, mp.insert(make_pair(p, name)));
	if (name == IDENEMY1 || name == IDENEMY2 || name == IDENEMY3)
		mpenemy.insert(make_pair(p, enemyinf(name)));
	if (name == IDTREE)Ntree++;
	if (name == IDSTONE)Nstone++;
	if (name == IDENEMY1)Nenemy1++;
	if (name == IDENEMY2)Nenemy2++;
	if (name == IDENEMY3)Nenemy3++;
	if (name == IDENEMY4)Nenemy4++;
}
void paintgaining(p_pvi obj, double pct) {
	if (obj==nullptr || pct <= 0)return;
	pct = pct * pi * 2;
	vector2 p = (*obj).s.first - realp + vector2(_winw / 2, _winh / 2); int name = (*obj).s.second;
	if (name == IDTREE) {
		setf(0x68B11F);
		fpie(p.x - treedemo.r, p.y - treedemo.r, p.x + treedemo.r, p.y + treedemo.r,
			p.x + 1, p.y, p.x + cos(pct) * 100, p.y - sin(pct) * 100);
	}
	if (name == IDSTONE) {
		setf(0x727272);
		fpie(p.x - stonedemo.r, p.y - stonedemo.r, p.x + stonedemo.r, p.y + stonedemo.r,
			p.x + 1, p.y, p.x + cos(pct) * 100, p.y - sin(pct) * 100);
	}
}
void paintmap() {
	getsighted(); getsightedenemy();
	{
		setf(GRAY180);
		vector2 v1 = vector2(mx1, my1) - realp + vector2(_winw / 2, _winh / 2);
		vector2 v2 = vector2(mx2, my2) - realp + vector2(_winw / 2, _winh / 2);
		if (v1.x >= 0)fbar(0, 0, (int)round(v1.x), _winh);
		if (v1.y >= 0)fbar(0, 0, _winw, (int)round(v1.y));
		if (v2.x <= _winw)fbar((int)round(v2.x), 0, _winw, _winh);
		if (v2.y <= _winh)fbar(0, (int)round(v2.y), _winw, _winh);
	}
	setd(0, 0, GRAY170);
	for (int i = 0, X = (20 - int(realp.x) % 20); i < 40; ++i, X += 20)
		pline(X, 0, X, _winh);
	for (int i = 0, Y = (20 - int(realp.y) % 20); i < 30; ++i, Y += 20)
		pline(0, Y, _winw, Y);
	for (p_ppvi i = mpobj.begin(); !i->isend; i=i->R) {
		pvi obj = (i->s)->s; vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (name == IDSTONE) {
			stonedemo.setposition(p.x, p.y);
			if ((i->s) == gainobj) {
				COLORREF c = stonedemo.fc; BYTE R = GetRValue(c), G = GetGValue(c), B = GetBValue(c);
				double CG = 3.0 / 4 * (1.0 - gainpct);
				COLORREF cc = RGB(R*CG, G*CG, B*CG);
				stonedemo.fc = cc;
				stonedemo.paint();
				stonedemo.fc = c;
				paintgaining(gainobj, gainpct);
			}
			else stonedemo.paint();
		}
	}
	for (p_ppvi i = mpobj.s->R; !i->isend; i=i->R) {
		pvi obj = (i->s)->s; vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (name == IDTREE) {
			treedemo.setposition(p.x, p.y);
			if ((i->s) == gainobj) {
				COLORREF c = treedemo.fc; BYTE R = GetRValue(c), G = GetGValue(c), B = GetBValue(c);
				double CG = 3.0 / 4 * (1.0 - gainpct);
				COLORREF cc = RGB(R*CG, G*CG, B*CG);
				treedemo.fc = cc;
				treedemo.paint();
				treedemo.fc = c;
				paintgaining(gainobj, gainpct);
			}
			else treedemo.paint();
		}
	}
	for (p_ppvi i = mpobj.s->R; !i->isend; i = i->R) {
		pvi obj = (i->s)->s; vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (name == IDFRUIT) {
			fruitdemo.setposition(p.x, p.y);
			fruitdemo.paint();
		}
	}
	for (p_ppve i = mpeobj.s->R; !i->isend; i = i->R) {
		vector2 p = i->s->s.first - realp + vector2(_winw / 2, _winh / 2);
		int id = i->s->s.second.ID;
		if (i->s->s.second.ID == IDENEMY4 && i->s->s.second.tmp > 0) {
			COLORREF FC = enemy4demo.fc1;
			enemy4demo.fc1 = inversergb(FC);
			paintenemy(id, p, i->s->s.second.ang);
			enemy4demo.fc1 = FC;
		}
		else paintenemy(id, p, i->s->s.second.ang);
	}
	for (p_pvv i = mpbullet.s->R; !i->isend; i=i->R) {
		vector2 p = (*i).s.first - realp + vector2(_winw / 2, _winh / 2);
		bulletdemo.setposition(p.x, p.y);
		bulletdemo.paint();
	}
}
void paintmist(double p) {
	if (p > 1.0)p = 1.0;
	beginPdot();
	double q = 1.0 - p; p = p * 150;
	for (int i = _pDataSize - 1; i >= 0; --i) {
		BYTE&P = _pData[i];
		P = (BYTE)(q*P + p);
	}
	endPdot();
}
void updatebullet() {
	for(p_pvv it=mpbullet.s->R; !it->isend; it=it->R){
		pvv S = it->s;
		vector2 a = S.first, b = S.second;
		vector2 A = a + b * (1.0 / norm(b))*velocitybullet;
		vector2 B = b - b * (1.0 / norm(b))*velocitybullet;
		it->s = make_pair(A, B);
		if ((b*B) < 1e-9)it=it->L,mpbullet.erase(it->R);
	}
}
void adjust(vector2 rp, double range, vector2&v, linkst<p_pvi>* S) {
	ref(times, 0, 1) {
		double a0 = 1e9, a1 = 1e9;
		double normv = norm(v);
		for (p_ppvi i = S->begin(); !i->isend; i = i->R) {
			pvi obj = (i->s)->s; vector2 p = obj.first - rp; int name = obj.second;
			double normp = norm(p);
			if (name == IDSTONE && normp<=range+stonedemo.r-1) {
				if ((v*p) < 0)continue;
				if ((v^p) >= 0) a0 = min(a0, acos((v*p) / normv / normp));
				else a1 = min(a1, acos((v*p) / normv / normp));
			}
			if (name == IDTREE && normp<=range+treedemo.r-1) {
				if ((v*p) < 0)continue;
				if ((v^p) >= 0) a0 = min(a0, acos((v*p) / normv / normp));
				else a1 = min(a1, acos((v*p) / normv / normp));
			}
		}
		if (rp.x <= mx1 || rp.x >= mx2) {
			vector2 p;
			if (rp.x <= mx1) p = vector2(-1.0, 0.0); else p = vector2(1.0, 0.0);
			if ((v*p) >= 0) {
				if ((v^p) >= 0)a0 = min(a0, acos((v*p) / normv / 1.0));
				else a1 = min(a1, acos((v*p) / normv / 1.0));
			}
		}
		if (rp.y <= my1 || rp.y >= my2) {
			vector2 p;
			if (rp.y <= my1)p = vector2(0.0, -1.0); else p = vector2(0.0, 1.0);
			if ((v*p) >= 0) {
				if ((v^p) >= 0)a0 = min(a0, acos((v*p) / normv / 1.0));
				else a1 = min(a1, acos((v*p) / normv / 1.0));
			}
		}
		if (a0 > pi / 2 && a1 > pi / 2)continue;
		if (a0 <= pi / 2 && a1 <= pi / 2) {
			v = vector2(0, 0); continue;
		}
		if (a0 <= pi / 2) {
			double a = atan2(v.y, v.x) - (pi / 2 - a0);
			double nv = normv * cos(pi / 2 - a0);
			v = vector2(nv*cos(a), nv*sin(a)); continue;
		}
		if (a1 <= pi / 2) {
			double a = atan2(v.y, v.x) + (pi / 2 - a1);
			double nv = normv * cos(pi / 2 - a1);
			v = vector2(nv*cos(a), nv*sin(a)); continue;
		}
	}
}
void makeenemy1route(pve&s) {
	vector2 p = s.first - realp; double sa = s.second.ang - pi / 2;
	if (norm(p) <= 400) {
		double sb = atan2(-p.y, -p.x), sd = sb - sa;
		while (sd < 0)sd += 2 * pi; while (sd > 2 * pi)sd -= 2 * pi;
		if (rand() % 4 > 0 && sd > 0.1&&sd < 2 * pi - 0.1) { if (sd < pi)sa += 0.1; else sa -= 0.1; }
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	else {
		if (rand() % 4 == 0)sa += 0.1; else if (rand() % 3 == 0)sa -= 0.1;
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	p = p + vector2(cos(sa), sin(sa))*velocityenemy1;
	p = p + realp; sa += pi / 2;
	if (p.x < mx1)p.x = mx1; if (p.x > mx2)p.x = mx2;
	if (p.y < my1)p.y = my1; if (p.y > my2)p.y = my2;
	s.first = p; s.second.ang = sa;
}
void makeenemy2route(pve&s) {
	linkst<p_pvi>* S = new linkst<p_pvi>; S->create();
	mpkd.collectitem(S, s.first, enemy2demo.r + max(treedemo.r, stonedemo.r));

	vector2 p = s.first - realp; double sa = s.second.ang - pi / 2;
	bool flag = 0;
	if (norm(p) <= 300) {
		double sb = atan2(-p.y, -p.x), sd = sb - sa;
		while (sd < 0)sd += 2 * pi; while (sd > 2 * pi)sd -= 2 * pi;
		if (rand() % 4 > 0 && sd > 0.1&&sd < 2 * pi - 0.1) { flag = 1; if (sd < pi)sa += 0.1; else sa -= 0.1; }
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	else {
		if (rand() % 4 == 0)sa += 0.1; else if (rand() % 3 == 0)sa -= 0.1;
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	vector2 v = flag?vector2():vector2(cos(sa), sin(sa))*velocityenemy2;
	p = p + realp; sa += pi / 2;
	adjust(p, enemy2demo.r, v, S); 
	p = p + v;

	S->clear(); delete S;
	s.first = p; s.second.ang = sa;
}
void makeenemy3route(pve&s) {
	linkst<p_pvi>* S = new linkst<p_pvi>; S->create();
	mpkd.collectitem(S, s.first, enemy3demo.r + max(treedemo.r, stonedemo.r));

	vector2 p = s.first - realp; double sa = s.second.ang - pi / 2;
	if (norm(p) <= 240) {
		double sb = atan2(-p.y, -p.x), sd = sb - sa;
		while (sd < 0)sd += 2 * pi; while (sd > 2 * pi)sd -= 2 * pi;
		if (sd > 0.8&&sd < 2 * pi - 0.8) { if (sd < pi)sa += 0.05; else sa -= 0.05; }
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	else {
		if (rand() % 4 == 0)sa += 0.05; else if (rand() % 3 == 0)sa -= 0.05;
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	vector2 v = vector2(cos(sa), sin(sa))*velocityenemy3;
	p = p + realp; sa += pi / 2;
	adjust(p, enemy3demo.r, v, S);
	p = p + v;

	S->clear(); delete S;
	s.first = p; s.second.ang = sa;
}
void makeenemy4route(pve&s) {
	if (s.second.tmp > 0) {
		s.second.tmp--;
		pve S = s; S.second.ang = pi * 2 - S.second.ang;
		if (!s.second.tmp) mpenemy.insert(S);
		return;
	}
	if (rand() % 2000 == 0) {
		s.second.tmp = 500;
		return;
	}

	linkst<p_pvi>* S = new linkst<p_pvi>; S->create();

	mpkd.collectitem(S, s.first, enemy4demo.r + max(treedemo.r, stonedemo.r));

	vector2 p = s.first - realp; double sa = s.second.ang - pi / 2;
	if (norm(p) <= 1000) {
		double sb = atan2(-p.y, -p.x), sd = sb - sa;
		while (sd < 0)sd += 2 * pi; while (sd > 2 * pi)sd -= 2 * pi;
		if (sd > 0.8&&sd < 2 * pi - 0.8) { if (sd < pi)sa += 0.05; else sa -= 0.05; }
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	else {
		if (rand() % 4 == 0)sa += 0.05; else if (rand() % 3 == 0)sa -= 0.05;
		while (sa < 0)sa += 2 * pi; while (sa > 2 * pi)sa -= 2 * pi;
	}
	double V = 1.0*(rand()%(int)(velocityenemy4*1000))/1000;
	vector2 v = vector2(cos(sa), sin(sa))*V;
	p = p + realp; sa += pi / 2;
	adjust(p, enemy4demo.r, v, S);
	p = p + v;

	S->clear(); delete S;
	s.first = p; s.second.ang = sa;
}
void updateenemy() {
	for (p_pve i = mpenemy.begin(); !i->isend; i = i->R) {
		int id = i->s.second.ID;
		if (id == IDENEMY1)makeenemy1route(i->s);
		if (id == IDENEMY2)makeenemy2route(i->s);
		if (id == IDENEMY3)makeenemy3route(i->s);
		if (id == IDENEMY4)makeenemy4route(i->s);
	}
}
void updatekilled() {
	for (p_pvv it1 = mpbullet.begin(); !it1->isend; it1=it1->R)
		for (p_pve it2 = mpenemy.begin(); !it2->isend; it2 = it2->R) {
			pvv t1 = (*it1).s; pve t2 = it2->s; int id = t2.second.ID;
			if (norm(t1.first - t2.first) <= getenemyR(id) + bulletdemo.r) {
				it1 = it1->L; mpbullet.erase(it1->R); 
				it2->s.second.life -= 1.0;
				if (it2->s.second.life < 1e-6) {
					mpenemy.erase(it2);
					if (id == IDENEMY1) {
						mpenemy.insert(make_pair(t2.first, enemyinf(IDENEMY3, t2.second.ang - pi / 3)));
						mpenemy.insert(make_pair(t2.first, enemyinf(IDENEMY3, t2.second.ang - pi * 2 / 3)));
						mpenemy.insert(make_pair(t2.first, enemyinf(IDENEMY3, t2.second.ang + pi / 3)));
						mpenemy.insert(make_pair(t2.first, enemyinf(IDENEMY3, t2.second.ang + pi * 2 / 3)));
					}
					declineN(id);
				}
				break;
			}
		}
}
void updatefruit() {
	for (p_pvi it = mp.begin(); !it->isend; it = it->R) {
		if (it->s.second == IDTREE && rand()%10000==0) {
			double ang = 1.0*(rand() % 10000) / 10000 * pi * 2;
			vector2 v(cos(ang), sin(ang)); v = v * (treedemo.r + fruitdemo.r);
			mp.insert(make_pair(it->s.first + v, IDFRUIT));
		}
		if (it->s.second == IDFRUIT && rand() % 30000 == 0) {
			it = it->L; mp.erase(it->R);
		}
	}
}
void getsighted() {
	mpobj.create();
	for (p_pvi i = mp.begin(); !i->isend; i=i->R) {
		pvi obj = i->s; vector2 p = obj.first - realp + vector2(_winw / 2, _winh / 2); int name = obj.second;
		if (!sighted(p, name))continue;
		mpobj.insert(i);
	}
}
void getsightedenemy() {
	mpeobj.create();
	for (p_pve i = mpenemy.begin(); !i->isend; i=i->R) {
		vector2 p = i->s.first - realp + vector2(_winw / 2, _winh / 2); int name = i->s.second.ID;
		if (!sighted(p, name))continue;
		mpeobj.insert(i);
	}
}
void clearsighted() {
	mpobj.clear(); mpeobj.clear();
}
void gettouch() {
	mptch.create();
	for (p_pvi i = mp.begin(); !i->isend; i=i->R) {
		pvi obj = i->s; vector2 p = obj.first - realp; int name = obj.second;
		double normp = norm(p);
		if (name == IDSTONE && normp >= stonedemo.r + figuredemo.r1 - 1)continue;
		if (name == IDTREE && normp >= treedemo.r + figuredemo.r1 - 1)continue;
		if (name == IDFRUIT && normp >= fruitdemo.r + figuredemo.r1 - 1)continue;
		mptch.insert(i);
	}
}
void gettouchenemy() {
	mpetch.create();
	for (p_pve i = mpenemy.begin(); !i->isend; i=i->R) {
		vector2 p = i->s.first - realp; int name = i->s.second.ID;
		double normp = norm(p);
		if (normp >= getenemyR(name) + figuredemo.r1 - 1)continue;
		mpetch.insert(i);
	}
}
void eraseall(p_pvi it) {
	declineN(it->s.second);
	if ((*it).s.second == IDTREE || (*it).s.second == IDSTONE) {
		pair<kdnode<p_pvi>*, p_ppvi> &s = kdpos[it];
		s.first->s.erase(s.second); kdpos.erase(it);
	}
	mp.erase(it);
}
void eraseallenemy() {
	for (p_ppve it = mpetch.begin(); !it->isend; it = it->R) {
		int name = it->s->s.second.ID;
		mpenemy.erase(it->s);
		it = it->L; mpetch.erase(it->R);
		declineN(name);
	}
}
void updateQ(bool isQ) {
	p_pvi id = nullptr;
	for (p_ppvi i = mptch.begin(); !i->isend; i = i->R)
		if ((i->s) == gainobj) { id = (i->s); break; }
	if (id != nullptr) {
		if (isQ) gainpct += velocityexploit;
		else gainpct = 0;
	}
	else {
		for (p_ppvi i = mptch.begin(); !i->isend; i = i->R) {
			int name = ((i->s)->s).second;
			if (name == IDTREE || name == IDSTONE) { id = (i->s); break; }
		}
		gainpct = 0;
	}
	gainobj = id;
	if (isQ) {
		if (gainpct >= 1.0) {
			if (gainobj->s.second == IDTREE) FP -= 2;
			if (gainobj->s.second == IDSTONE) FP -= 3;
			if (gainobj->s.second == IDTREE) number_wood++, Ntree--, mist += 200;
			if (gainobj->s.second == IDSTONE) number_stone++, Nstone--, mist += 500;
			eraseall(gainobj);
			gainobj = nullptr; gainpct = 0;
		}
	}
}
bool updatetouchenemy() {
	bool res = (mpetch.sz>0);
	for (p_ppve it = mpetch.begin(); !it->isend; it = it->R) {
		int id = it->s->s.second.ID;
		HP -= getenemyatk(id);
	}
	eraseallenemy();
	return res;
}
void updateeatfruit() {
	for (p_ppvi it = mptch.begin(); !it->isend; it = it->R) {
		if (it->s->s.second == IDFRUIT) {
			FP = FP + 10; if (FP >= 100.0)FP = 100.0;
			eraseall(it->s); it = it->L; mptch.erase(it->R);
		}
	}
}
void initkdtree() {
	kdpos.clear();
	mpkd.create(mx1, my1, mx2, my2, 0.01, 0.01);
	for (p_pvi it = mp.begin(); !it->isend; it = it->R)
		if (it->s.second == IDTREE || it->s.second == IDSTONE)
			kdpos[it]=mpkd.insert(it->s.first, it);
}

void _restart1(bool ifload = 0) {
	flushmouse(); 

	//左上角文本框信息初始化
	textbox TBtree, TBstone, TBfps, TBmist, TBhp, TBfp;
	TBfps.init();
	TBfps.setbox(0, 0, _winw, _winh);
	TBfps.setstyle(GRAY80, 20, 0, "等线", lgleft | lgtop);
	TBfps.text = ""; TBfps.paint();
	TBmist = TBfps;
	TBmist.setbox(0, TBfps.ty2, _winw, _winh);
	TBmist.text = ""; TBmist.paint();
	TBhp = TBmist;
	TBhp.setbox(0, TBmist.ty2, _winw, _winh);
	TBhp.text = "HP: "; TBhp.paint();
	TBfp = TBhp;
	TBfp.setbox(0, TBhp.ty2, _winw, _winh);
	TBfp.text = "FP: "; TBfp.paint(); 
	TBfp.x1 = (TBhp.tx2 - TBhp.tx1) - (TBfp.tx2 - TBfp.tx1); TBfp.paint();

	//右上角~
	TBtree.init();
	TBtree.setbox(0, 0, _winw, _winh);
	TBtree.setstyle(rgb(50, 100, 0), 20, 0, "等线", lgright | lgtop);
	TBtree.text = ""; TBtree.paint();
	TBstone = TBtree;
	TBstone.setbox(0, TBtree.ty2, _winw, _winh);
	TBstone.text = ""; TBstone.paint();
	
	//载入存档或初始化变量
	if (ifload)loadgame();else initgame();

	//额外变量初始化
	ns_shop::_inputshopdata();
	gainobj = nullptr; gainpct = 0;
	initkdtree();
	int shoottimes = 0;

	//计时器变量
	int tick = 0, injuredtick = -1e9, shoottick = -1e9; int t = 0, rest = 0; DWORD last = GetTickCount();

	while (!_isquit) {
		//真-计时
		currenttick++;

		//计时
		tick++;
		t++;
		if (GetTickCount() >= last + 1000) { last += 1000; rest = t; t = 0; }

		//如果窗口未激活
#ifndef DEBUGGING
		if (!iswndactive()) {
			while (!iswndactive()) peekmsg(), delay(1);
			last = GetTickCount();
			flushkey(); flushmouse();
			while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) peekmsg(), delay(1);
			continue;
		}
#endif

		//鼠标左键
		vector2 ms(getmousex(hwnd) - _winw / 2, getmousey(hwnd) - _winh / 2);
		figure.angle = atan2(ms.y, ms.x) + pi / 2;
		if (GetAsyncKeyState(VK_LBUTTON)&&tick - shoottick >= velocityreload && number_stone>0) {
			shoottick = tick;
			shoottimes = 1%multipleshoot;
			number_stone--;
			mist += 100;
			double a = atan2(ms.y, ms.x), ca = cos(a), sa = sin(a); vector2 v(ca, sa);
			mpbullet.insert(make_pair(v*figuredemo.r1 + realp, v * rangebullet)); 
		}
		if (shoottimes > 0 && tick - shoottick >= velocityreload/8) {
			shoottick = tick;
			mist += 100 / shoottimes;
			shoottimes = (shoottimes + 1) % multipleshoot;
			double a = atan2(ms.y, ms.x), ca = cos(a), sa = sin(a); vector2 v(ca, sa);
			mpbullet.insert(make_pair(v*figuredemo.r1 + realp, v * rangebullet));
		}

		if (tick % 50 == 0) {
			if (rand() % 50 == 0)produceobj(IDTREE);
			if (rand() % 30 == 0)produceobj(IDSTONE);
			if (currenttick >= 1500) {
				if (rand() % 10 == 0)produceobj(IDENEMY1);
				if (rand() % 5 == 0)produceobj(IDENEMY2);
			}
		}
		
		//处理地图信息
		updatebullet();
		updateenemy();
		updatekilled();
		updatefruit();

		//与物体接触或按Q
		gettouch(); gettouchenemy(); 
		updateQ(GetAsyncKeyState('Q') & 0x8000);
		updatetouchenemy();
		updateeatfruit();

		//按E进入商店
		if (GetAsyncKeyState('E') & 0x8000) {
			ns_shop::_shop();
			flushkey(); flushmouse();
			while (GetAsyncKeyState(VK_ESCAPE))peekmsg(), delay(1);
			continue;
		}

		//WSAD移动，调整加速度
		vector2 a;
		if (GetAsyncKeyState('W') & 0x8000)a.y -= 0.23;
		if (GetAsyncKeyState('S') & 0x8000)a.y += 0.23;
		if (GetAsyncKeyState('A') & 0x8000)a.x -= 0.23;
		if (GetAsyncKeyState('D') & 0x8000)a.x += 0.23;
		if (a.x != 0 || a.y != 0)a = a * (1.0 / norm(a));
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			savegame(); break;
		}

		//调整速度
		realv = realv + a;
		double nv = norm(realv);
		if (nv > velocity) realv = realv * (velocity / norm(realv)), nv = velocity;
		if (nv < 0.1)realv = { 0,0 }, nv = 0; else realv = realv * ((nv - 0.2) / nv);
		adjust(realp, figuredemo.r1, realv, &mptch);
		if (mptch.sz) realv = realv * 0.8;
		realp = realp + realv;

		//修改mist, HP, FP值
		mist += 1.5;
		mist -= min(Ntree*0.01, mist*0.01);
		HP -= min((1.0*mist / 100000)*(1.0*mist / 100000)*0.2, 0.01);
		if (HP<100.0)HP += 0.004;
		FP -= 0.003;
		if (FP <= 50.0) HP -= 0.01;
		if (FP <= 10.0) HP -= 0.1;

		//开始绘制地图
		clearscreen(GRAY200);
		paintmap();
		figure.paint();
		paintmist(min(0.4, 1.0*mist / 60000) * sin(2 * pi*tick / 500) + min(0.4, 2.0*mist / 60000));
		
		//绘制各种文本
		string snf = "FPS: "; snf += constr(rest);
		TBfps.text = snf.c_str(); TBfps.paint();
		string snm = "Mist: "; snm += constr(mist);
		TBmist.text = snm.c_str(); TBmist.paint();
		string snw = "Number Of Wood: "; snw += constr(number_wood);
		TBtree.text = snw.c_str(); TBtree.paint();
		string sns = "Number Of Stone: "; sns += constr(number_stone);
		TBstone.text = sns.c_str(); TBstone.paint();
		string snhp = "HP: "; snhp += constr((int)round(HP));
		TBhp.textcolor = (tick - injuredtick <= 50) ? RGB(255,0,0) : GRAY80; 
		TBhp.text = "HP: "; TBhp.paint();
		setd(0, 0, RGB(200, 22, 9)); dbar(TBhp.tx2, TBhp.ty1, TBhp.tx2 + 200, TBhp.ty2);
		setf(RGB(200, 22, 9)); fbar(TBhp.tx2, TBhp.ty1, TBhp.tx2 + (int)round(HP) * 2, TBhp.ty2);
		TBhp.text = snhp.c_str(); TBhp.paint();
		string snfp = "FP: "; snfp += constr((int)round(FP));
		TBfp.textcolor = GRAY80;
		TBfp.text = "FP: "; TBfp.paint();
		setd(0, 0, RGB(70, 130, 200)); dbar(TBfp.tx2, TBfp.ty1, TBfp.tx2 + 200, TBfp.ty2);
		setf(RGB(70,130,200)); fbar(TBfp.tx2, TBfp.ty1, TBfp.tx2 + (int)round(FP) * 2, TBfp.ty2);
		TBfp.text = snfp.c_str(); TBfp.paint();

#ifdef DEBUGGING
		textbox tbtk;
		tbtk.init();
		tbtk.setbox(0, 0, _winw, _winh);
		tbtk.setstyle(GRAY80, 20, 0, "等线", lgtop | lgcenterhorizontal);
		string sntk = constr(currenttick); sntk = "Current Tick : " + sntk;
		tbtk.text = sntk.c_str();
		tbtk.paint();
#endif

		//绘制到设备
		flushpaint();

		//存档, 判断是否死亡
		if (!(tick % 1500)) savegame();
		if ((int)round(HP) <= 0)break;

		//消息循环
		peekmsg(); delay(1);
	}
	mpkd.clear(); kdpos.clear();
	mp.clear(); mpobj.clear(); mptch.clear();
	mpenemy.clear(); mpeobj.clear(); mpetch.clear();
	mpbullet.clear();
}

BYTE*rcData;
tagRGBTRIPLE arrbitmap[800][600]; bool flagarr;
int Sr[800][600], Sg[800][600], Sb[800][600];

void initrcData() {
	if (flagarr)return; flagarr = 1;
	string fileinfo = UseCustomResource(IDB_BITMAP1, _hinst, rcData);
	getarrbitmap(arrbitmap , rcData, 800, 600);
	delete[] rcData;
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
}

void paintbmp(int x, int y, int X, int Y) {
	if (!flagarr) initrcData();
	beginPdot();
	int w = 800, h = 600;
	ref(i, x, X)ref(j, y, Y) {
		int r = 0, g = 0, b = 0, t = 0;
		int p = 4 * j / h + 2;

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

		t = (min(i + p, w - 1) - max(i - p, 0) + 1)*(min(j + p, h - 1) - max(j - p, 0) + 1);

		r /= t; g /= t; b /= t;
		double q = 1.0*max(j - 300, 0) / 600;
		r = (1 - q)*r + q * 200; g = (1 - q)*g + q * 200; b = (1 - q)*b + q * 200;
		Pdot(i, j, r, g, b);
	}
	endPdot();
}
void Paintbmp(int x, int y, int X, int Y) {
	int w = 800, h = 600;
	if (!flagarr) initrcData();
	beginPdot();
	ref(i, x, X)ref(j, y, Y) {
		int r, g, b, t;
		int p = 10;
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
		t = (min(i + p, w - 1) - max(i - p, 0) + 1)*(min(j + p, h - 1) - max(j - p, 0) + 1);
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

	button b1, b2, b3, b4, bnext;
	b1.init();
	b1.setstyle(GRAY170, BLACK, BLACK, GRAY150, GRAY140, GRAY120, 24, 0, "黑体");
	b2 = b3 = b4 = bnext = b1;
	b4.buttoncolor[0] = GRAY100;
	b1.setbox(660, 70, 760, 170);
	b2.setbox(660, 170, 760, 270);
	b3.setbox(660, 270, 760, 370);
	b4.setbox(660, 370, 760, 470);
	bnext.setbox(660, 470, 760, 520);
	bnext.text = "CONFIRM";
	
	picker p[3];
	p[0].init();
	p[0].setbox(40, 120, 640, 520);
	p[0].setstyle(5);
	p[1] = p[2] = p[0];
	flushpaint();

	textbox t, trgb;
	t.init();
	t.text = "Choose a color for your character : ";
	t.setbox(p[0].x1, 70, p[0].x2, 120);
	t.setstyle(BLACK, 30, 0, "微软雅黑", lgtop | lgleft);
	t.paint();
	trgb.init();
	trgb.setbox(p[0].x1, t.ty1, p[0].x2, t.ty2);
	trgb.setstyle(BLACK, 30, 0, "微软雅黑", lgtop | lgright);
	
	figureimage fg1, fg2, fg3, fg4;
	fg1.setposition((b1.x1 + b1.x2) / 2, (b1.y1 + b1.y2) / 2);
	fg2.setposition((b2.x1 + b2.x2) / 2, (b2.y1 + b2.y2) / 2);
	fg3.setposition((b3.x1 + b3.x2) / 2, (b3.y1 + b3.y2) / 2);
	fg4.setposition((b4.x1 + b4.x2) / 2, (b4.y1 + b4.y2) / 2);

	int current_p = 0;
	int cury = 70, idealy = 70;
	
	while (!_isquit) {
		peekmsg(); delay(1);
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
			Paintbmp(trgb.tx1, trgb.ty1, trgb.tx2, trgb.ty2);
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
			Paintbmp(trgb.tx1, trgb.ty1, trgb.tx2, trgb.ty2);
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
		Paintbmp(655 - 3 / 2, cury - 3 / 2, 655 + 3 / 2, cury + 100 + 3 / 2);
		Paintbmp(765 - 3 / 2, cury - 3 / 2, 765 + 3 / 2, cury + 100 + 3 / 2);
		if (cury < idealy)cury += 10; if (cury > idealy)cury -= 10;
		setd(0, 3, BLACK); pline(655, cury, 655, cury + 100); pline(765, cury, 765, cury + 100);
		flushpaint();
	}
}
void _main() {
	textbox t, t1, t2, t3;

#ifndef DEBUGGING
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
#endif

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
			_restart1(1);
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