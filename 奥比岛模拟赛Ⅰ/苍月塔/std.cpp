using namespace std;
int main() {}
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>
#include <cassert>
namespace OI {
struct LS {
	int inline operator [] (int a) {
		return a << 1;
	}
}ls;
struct RS {
	int inline operator [] (int a) {
		return a << 1 | 1;
	}
}rs;
typedef long long lld;
typedef double lf;
typedef unsigned u;
typedef unsigned char uc;
typedef unsigned long long llu;
typedef long double Lf;
const lf PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const lld LINF = (lld)INF << 32 | INF;
const int DST = 0, NXT = 1, VAL = 2, FLOW = 2, CST = 3;
const int MXN = 5e3 + 10;
const int MXV = 5e6 + 10;
struct _Main {
	lld Ahp, Aam, Aatk, Acst;
	lld Nhp, Nam, Natk, Ncst;
	lld Am, Atk, Hp;
	int n;
	void copy() {
		Ahp = Nhp;
		Aam = Nam;
		Aatk = Natk;
		Acst = Ncst;
	}
	void update() {
		if (Ncst < Acst) {
			copy();
		} else
		if (Ncst == Acst) {
			if (Nhp < Ahp || Nhp == Ahp && Nam < Aam) {
				copy();
			} 
		}
	}
	lld Csthp, Cstam, Cstatk;
	lld Vam, Vatk;
	lld Oam, Ohp, Oatk;
	lld hp[MXN], am[MXN], atk[MXN], num[MXN];
	
	lld times[MXV], val[MXV];
	lld Ntimes, Nval;
	inline lld up(lld a, lld b) {
		return (a + b - 1) / b;
	}
	_Main() {
		lld low = 0, high = 0;
		Acst = LINF;
		read(n);
		read(Ohp); read(Oam); read(Oatk);
		read(Csthp); read(Cstam); read(Vam); read(Cstatk); read(Vatk);
		for (int i = 1; i <= n; i++) {
			read(num[i]);
			read(hp[i]);
			read(am[i]); 
			read(atk[i]);
			low = max(low, up(am[i] - Oatk + 1, Vatk));
			high = max(high, up(hp[i] + am[i], Vatk));
			Am =  max(Am, up(atk[i] - Oam, Vam));
			if (atk[i] <= Oam) {
				n--; 
				i--;
			}
			//这个卡一下, 因为low已经被更新了，所以不会被卡
		}
		Natk = Oatk + low * Vatk;
		for (int i = 1; i <= n; i++) {
			if (atk[i] <= Oam) continue;
			if (Vam == 0) {
				exit(0);
			}
			lld pos = (atk[i] - Oam) / Vam;
			lld atktimes = up(hp[i], Natk - am[i]);
			if (pos != Am) {
				times[pos] += num[i] * atktimes; 
				val[pos] += num[i] * ((atk[i] - Oam) % Vam) * atktimes;
			} else {
				Nval += num[i] * ((atk[i] - Oam) % Vam) * atktimes;
				Ntimes += num[i] * atktimes;
			}
			int lst = low;
			for (int st = 1, ed; st <= hp[i]; st = ed + 1) {// hp / (Natk - am)
				ed = hp[i] / (hp[i] / st);
				if (st != ed && hp[i] % ed == 0) {
					--ed;
				}
				Atk = up(st + am[i] - Oatk, Vatk);
				if (Atk > lst) {
					lst = Atk;
					add(Atk, i);
				}
			}
		}
//		cerr <<"[" << low << ", " << high << "]" << endl;
		for (Atk = low; Atk <= high; ++Atk) {
//			cerr << "Atk = " << Atk << endl;
			Natk = Oatk + Atk * Vatk;
			lld Latk = Oatk + (Atk - 1) * Vatk;
			for (int e = head[Atk]; e; e = edge[e][NXT]) {
				int nd = edge[e][DST];
				lld pos = (atk[nd] - Oam) / Vam;
				lld delta = up(hp[nd], Natk - am[nd]) - up(hp[nd], Latk - am[nd]);
				delta *= num[nd];
				if (pos < Am) {
					times[pos] += delta; 
					val[pos] += ((atk[nd] - Oam) % Vam) * delta;
				} else {
					Ntimes += delta; 
					Nval += (atk[nd] - Nam) * delta;
				}
			}
			while (Am > 0 && 
				  max(Nval + val[Am - 1] + (lf)Ntimes * Vam + 1 - Ohp, 0.0) * Csthp
				- max(Nval + 1 - Ohp, 0LL) * Csthp - Cstam < 0) {//卡一下没有+1的
				--Am;
				Nval += val[Am] + Ntimes * Vam;
				Ntimes += times[Am];
			}
			Nam = Oam + Am * Vam;
			Nhp = max(Ohp, Nval + 1);		
			Hp = Nhp - Ohp;
			Ncst = Atk * Cstatk;
			Ncst += Am * Cstam;
			Ncst += Hp * Csthp;
			update();
		}
		printf("%lld\n%lld %lld %lld", Acst, Ahp, Aam, Aatk);
	}
	int head[MXV];
	int edge[MXN * MXN][2];
	int eidx;
	void add(int pos, int val) {
		eidx++;
		edge[eidx][DST] = val;
		edge[eidx][NXT] = head[pos];
		head[pos] = eidx;
	}
template <typename Type>
	void read(Type &a) {
		char t, f = 1;
		while (!isdigit(t = getchar())) {
			f = t == '-' ? -1 : f;
		}
		a = t - '0';
		while ( isdigit(t = getchar())) {
			a *= 10; a += t - '0';
		}
		a *= f;
	}
}std;
}

