using namespace std;
#include<fstream>
#include<cstdlib>
#include<cmath>
#define AC 0
#define WA 1


const double EPS = 1e-2 + 1e-6;
bool equal(double a, double b) {
    return a < b + EPS && a > b - EPS; 
}
int pf(int a) {
	return a * a;
}
int vis[501200];
int cnt;
int ans;
bool push (int val) {
	if (val <= 0 || val > ans || vis[val]) {
		return 0;
	} 
	vis[val] = 1;
	cnt++;
	return 1;
}
int main(int argc, char *args[])  
{
    ifstream f_in(args[1]);
	ifstream f_out(args[2]);
	ifstream f_user(args[3]);
    int i, j, k;
	int lst, in;
	int n;
	int zhuzi = 0;
	f_in >> n;
	f_user >> lst;
	ans = ((n + 1) * (n + 1) >> 1) - 1;
	if (push(lst) == 0) {
		return WA;
	}
	zhuzi++;
	while (f_user >> in) {
	    if (push(in) == 0) {
	    	return WA;
	    }
        if ((pf ((int)sqrt(in + lst)) != in + lst) || in > lst) {
        	zhuzi++;
        	if (zhuzi > n) {
        		return WA;
        	}
        }
        lst = in;
	}
	
    return cnt == ans && zhuzi == n ? AC : WA;  
}  




















