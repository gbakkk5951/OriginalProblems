#include <bits/stdc++.h>
using namespace std;
const int MXN = 52;
int r[MXN][MXN];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		int flag = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", &r[i][j]);
			}
		}
		
		for (int i = 1; i <= n; ++i) {
			if (!r[i][i]) {//反身性
				flag = 1;
				goto End;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				/*if (r[i][j]) {
					for (int k = 1; k <= n; ++k) {
						if (r[j][k] && ! r[i][j]) {//传递性
							flag = 1;
							goto End;
						}
					}
				}*/
				int sup = -1, inf = -1;
				for (int k = 1; k <= n; ++k) {//最紧的上下界
					if (r[k][i] && r[k][j]) {
						if (sup == -1 || r[sup][k]) {
							sup = k;
						} 
					}
					if (r[i][k] && r[j][k]) {
						if (inf == -1 || r[k][inf]) {
							inf = k;
						}
					}
				}
				if (min(sup, inf) == -1) {//不存在上/下界
					flag = 1;
					goto End;
				}
				for (int k = 1; k <= n; ++k) {//唯一性
					if (r[k][i] && r[k][j]) {
						if (!r[k][sup]) {
							flag = 1;
							goto End;
						}
					}
					if (r[i][k] && r[j][k]) {
						if (!r[inf][k]) {
							flag = 1;
							goto End;
						}
					}
				}
				
				
			}
		}
		End:
		puts(flag ? "N" : "Y"); 
	}
	return 0;
}
