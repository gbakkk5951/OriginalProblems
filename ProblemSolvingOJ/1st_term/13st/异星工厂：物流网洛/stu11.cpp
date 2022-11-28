#include<bits/stdc++.h>
const int N = 50 + 5;
int arr[N][N];
int is_re, is_tr, is_la;
int sup, inf;

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		is_re = is_tr = is_la = 1;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &arr[i][j]);
			}
		}
		
		for (int i = 1; i <= n; i++) {//判自反
			if (!arr[i][i]) {
			    is_re = 0;
			    break;
            }
		}
		if (!is_re) {
			printf("N\n");
			continue;
		}
		for (int i = 1; i <= n; i++) //判传递
			for (int j = 1; j <= n; j ++) 
				for (int k = 1; k <= n; k++) 
					if (arr[i][j] && arr[j][k])
						if (!arr[i][k]) {
						    is_tr = 0;
							break;	
						}
		if (!is_tr) {
			printf("N\n");
			continue;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				sup = inf = 0;
				if (i == j) 
				    continue;
                for (int k = 1; k <= n; k++) {//判上确界
                	if (arr[i][k] && arr[j][k]) {
                		if (sup == 0)
                		    sup = k;
            		    else {
            		    	if (!arr[sup][k] && !arr[k][sup]) {
            		    		is_la = 0;
            		    		break;
							}
							if (arr[k][sup] == 1)
							    sup = k;
						}          		        
					}
				}
				for (int k = 1; k <= n; k++) {//判下确界
                	if (arr[k][i] && arr[k][j]) {
                		if (inf == 0)
                		    inf = k;
            		    else {
            		    	if (!arr[inf][k] && !arr[k][inf]) {
            		    		is_la = 0;
            		    		break;
							}
							if (arr[inf][k] == 1)
							    inf = k;
						}          		        
					}
				}
				if (!is_la || !sup || !inf) {
					is_la = 0;
					break;
				}
			}
			if (!is_la) {
				printf("N\n");
				break;
			}			
		}
		if (is_re && is_tr && is_la)
		    printf("Y\n");
	}
	return 0;
}

