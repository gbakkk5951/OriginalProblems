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
struct _Main {
	lld hp[MXN], am[MXN], atk[MXN], k[MXN];
	lld Csthp, Cstam, Cstatk;
	lld Vam, Vatk;
	lld Ohp, Oam, Oatk;
	lld Nhp, Nam, Natk, Ncst;
	lld Ahp, Aam, Aatk, Acst;
	lld Hp, Am, Atk;
	void copy() {
		Ahp = Nhp;
		Aam = Nam;
		Aatk = Natk;
		Acst = Ncst;
	}
	void update() {
//		printf("now %lld %lld %lld $%lld\n", Ahp, Aam, Aatk, Acst);
		if (Ncst < Acst) {
			copy();
		} else
		if (Ncst == Acst) {
			if (Nhp < Ahp || Nhp == Ahp && Nam < Aam) {
				copy();
			}
		}
	}
	int n;
	inline lld up(lld a, lld b) {
		return (a + b - 1) / b;
	}
	lld calcHp() {//用lf 算 > 1e18 的话return LINF else return ret 因为Cstam很小，所以不怕精度问题
		lf ret = 0;
		for (int i = 1; i <= n; i++) {
			if (atk[i] > Nam) {
				ret += (lf)up(hp[i] , Natk - am[i]) * (atk[i] - Nam) * k[i];
			}
		}
		if (ret > 1e18) return LINF;
		return max((lld)round(ret - Ohp + 1), 0LL);// 血量 + 1
	}
	_Main() {
		read(n);
		read(Ohp); read(Oam); read(Oatk);
		read(Csthp); read(Cstam); read(Vam); read(Cstatk); read(Vatk);
		lld low = 0, high = 0;
		for (int i = 1; i <= n; i++) {
			read(k[i]); read(hp[i]); read(am[i]); read(atk[i]);
			low = max(low, up(am[i] + 1 - Oatk, Vatk));
			high = max(high, up(am[i] + hp[i] - Oatk, Vatk));
			Am = max(Am, up(atk[i] - Oam, Vam));
		}
		Acst = LINF;
		Nam = Oam + Am * Vam;//初值没赋
		for (Atk = low; Atk <= high; Atk++) {
			Natk = Oatk + Atk * Vatk;
			Hp = calcHp();
			while (Am > 0) {
				--Am;
				Nam = Oam + Am * Vam;
				lld tmp = calcHp();
				if (!((lf)(tmp - Hp) * Csthp - Cstam < 0)) {
					++Am;
					break;
				} else {
					Hp = tmp;
				}
			}
			Nam = Oam + Am * Vam;
			Nhp = Ohp + Hp;
			Ncst = Hp * Csthp + Am * Cstam + Atk * Cstatk;
			update();
		}
		printf("%lld\n%lld %lld %lld", Acst, Ahp, Aam, Aatk);
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
