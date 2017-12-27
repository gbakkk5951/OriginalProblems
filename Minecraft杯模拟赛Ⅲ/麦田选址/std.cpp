using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<algorithm>
namespace Protector{

struct Point{
	int x,y;
	bool friend operator < (const Point &a,const Point &b){
		return a.x<b.x;
	}
}arr[210];
int y[210];
struct _Main{
	template<typename Type>
		void read(Type &a){
			char t;
			while(!isdigit(t=getchar()));
			a=t-'0';
			while( isdigit(t=getchar())){
				a*=10;a+=t-'0';
			}
		}
	int n,m;	
	int num;
	int ans;
	_Main(){
		int i,j,k;
		int a,b,c;
		int l,r;
		int ny;
		read(n);read(m);read(num);
		for(i=1;i<=num;i++){
			read(arr[i].x);
			read(arr[i].y);
			y[i]=arr[i].y;
		}
		y[num+1]=m+1;
		sort(y,y+num+2);
		ny=unique(y,y+num+2)-y;
		sort(arr+1,arr+num+1);
		int up,down;
		for(i=0;i<ny-1;i++){
			for(j=i+1;j<ny;j++){
				l=y[i];r=y[j];
				if(r-l-1<=ans)continue;
				up=0;
				for(k=1;k<=num;k++){
					ans=max(ans,min(r-l-1,arr[k].x-up-1));
					if(arr[k].y<r && arr[k].y>l){
						up=arr[k].x;
					}
				}
				ans=max(ans,min(r-l-1,n+1-up-1));
			}
		}
		printf("%d",ans);
	}
	
}std;

}
