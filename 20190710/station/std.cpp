using namespace std;
int main(){}
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cmath>

const double eps=1e-1;
struct _Main{
typedef long long ll;

template <typename Type>
void read(Type &a){
	char t;
	while(!isdigit(t=getchar()));
	a=t-'0';
	while(isdigit(t=getchar()))	{
		a*=10;
		a+=t-'0';
	}
}
double left;
double ans[2];
double calc(){
	double ret=0;
	int i,j,k;
	j=0;
	for(i=0;i<m;i++){
		while(j+1<n && fabs(d[j+1]+left-p[i])<fabs(d[j]+left-p[i])){
			j++;
		}
		ret+=fabs(d[j]+left-p[i]);
	}return ret;
}


int l,m,n;
int p[305],d[305];
_Main(){
	double temp;
	int i,j,k;
	read(l);
	read(m);
	for(i=0;i<m;i++){
		read(p[i]);
	}
	read(n);
	for(i=1;i<n;i++){
		read(d[i]);
	}
	left=0;
	ans[0]=calc();
	ans[1]=left;

	left=l-d[n-1];
	temp=calc();
	if(temp>ans[0]){
		ans[0]=temp;
		ans[1]=left;		
	}
	
	
	for(i=1;i<n;i++){
		for(j=0;j<m;j++){
			left=p[j]-(d[i]-d[i-1])/2.0-d[i-1];
			if( left>-eps && (left +d[n-1]  < l+eps )){
				temp=calc();
				if(temp>ans[0]+eps || ((temp>ans[0]-eps) && left<ans[1]-eps)){
					ans[0]=temp;
					ans[1]=left;		
				}
			}
		}
	}
	printf("%.1lf %.1lf",ans[1],ans[0]);
	fclose(stdout);
}	
	
	
	
	
	
}boat;
