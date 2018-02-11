using namespace std;
#include<fstream>
#include<cstdlib>
#define AC 0
#define WA 1
const double EPS = 1e-2 + 1e-6;
bool equal(double a, double b) {
    return a < b + EPS && a > b - EPS; 
}

int main(int argc, char *args[])  
{
    ifstream f_in(args[1]);
	ifstream f_out(args[2]);
	ifstream f_user(args[3]);
    double u_ans, std_ans;
	int i, j, k;
	int a, b;
	int n, m;

	f_in >> n >> m;
	for (i = 1; i <= n + m; i++) {
	    f_out >> std_ans;
	    f_user >> u_ans;
        if (!equal(std_ans, u_ans)) {
            return WA;
        }
	    
	}
    return AC;  
}  




















