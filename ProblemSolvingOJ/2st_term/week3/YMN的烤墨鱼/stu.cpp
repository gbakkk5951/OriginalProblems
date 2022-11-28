#include <bits/stdc++.h>
using namespace std;
long long T, sum, tem, lch, flag;
		long long arr[(int)1e6 + 9] = {};
		long long key[(int)1e6 + 5] = {};
int main (){
	scanf("%d", &T);
	while (T--){
		long long n = 0, k = 0;
		scanf("%d", &n);
		long long mat[10005] = {};
		for (int i = 1; i <= n; i++){
			scanf("%d", &arr[i]);
		}
		lch = 1;
		for (int i = 1; i <= n; i++){
			if (key[i] == 1){
				continue;
			}
			key[i] = 1;
			tem = i;
			flag = 1;
			tem = arr[tem];
			key[tem] = 1;
			while(tem != i){
				tem = arr[tem];
				key[tem] = 1;
				flag++;
			}
			for (int j = 2; j <= 5000; j++){
				long long count = 0;
				long long ss = flag;
				if (flag < j){
					break;
				}
				while((flag % j == 0)&&(flag >= 2)){
					flag = flag / j;
					count++;
				}
				if (count > mat[j]){
					mat[j] = count;
				}
			}
		}
		for (int i = 2; i <= 5000; i++){
			if (mat[i] != 0){
				for (int j = 0; j < mat[i]; j++){
					lch = (lch * i) % 998244353;
				}
			}
		}
		printf("%ld", lch);
		printf("\n");
	}
return 0;
}
 
