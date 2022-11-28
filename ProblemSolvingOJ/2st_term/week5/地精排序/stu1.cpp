#include <bits/stdc++.h>
using namespace std;
long long  mat[500002][2],tmp[500002][2];
long long ans, sum, all_the_ans;
bool bigger(long long i, long long j){
	if (mat[i][1] > mat[j][1]){
		return true;
	}else if (mat[i][1] == mat[j][1]){
		if (mat[i][2] > mat[j][2]){
			return true;
		}
		else if(mat[i][2] < mat[j][2]){
			return false;
		}
	}else if (mat[i][1] < mat[j][1]){
		return false;
	}
}

void Merge(long long l, long long m, long long r){
    long long i = l;
    long long j = m + 1;
    long long k = l;
    while((i <= m) && (j <= r)){
        if(bigger(i, j)){
            tmp[k++][1] = mat[j++][1];
            tmp[k][2] = mat[j][2];
            ans += m - i + 1;
        }else{
            tmp[k++][1] = mat[i++][1];
            tmp[k][2] = mat[i][2];
        }
    }
    while(i <= m){
		tmp[k++][1] = mat[i++][1];
        tmp[k][2] = mat[i][2];
	} 
    while(j <= r){
		tmp[k++][1] = mat[j++][1];
        tmp[k][2] = mat[j][2];
	} 
    for(long long i = l; i <= r; i++)
    	mat[i][1] = tmp[i][1];
    	mat[i][2] = tmp[i][2];
}

void Merge_sort(long long l, long long r){
    if(l < r){
        long long m = ((l + r) / 2);
        Merge_sort(l, m);
        Merge_sort(m + 1, r);
        Merge(l, m, r);
    }
}

void third(long long n){
	sum = 1;
	long long x = mat[1][1];
	long long y = mat[1][2];
	for (long long i = 2; i <= n; i++){
		if(mat[i][1] < x){
			sum++;
			x = mat[i][1];
			y = mat[i][2];
		}
		else if (mat[i][1] == x){
			if (mat[i][2] < y){
				sum++;
				x = mat[i][1];
				y = mat[i][2];
			}
		}
	}
}
int main(){
    long long n = 0;
    scanf("%lld", &n);
    for(long long i = 1; i <= n; i++){
		for (int j = 1; j <= 2; j++){
			scanf("%lld", &mat[i][j]);
		}
	}
    ans = 0;
    third(n);
    Merge_sort(1, n);
    all_the_ans = n + (2 * ans) - sum;
    cout << all_the_ans;
    return 0;
}
