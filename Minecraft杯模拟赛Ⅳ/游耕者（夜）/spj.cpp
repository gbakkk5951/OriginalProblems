#include<fstream>
#include<cstdlib>
#define ac 0
#define wa 1
using namespace std;
int n;
bool vis[400010];
long long ans,tot;
int x[400010],y[400010];
int inline getdis(int a,int b){
	return abs(x[a]-x[b])+abs(y[a]-y[b]);
}
int main(int argc,char *args[])  
{
	int i,j,k;
	int a,b;
	
	ifstream f_out(args[2]);
	f_out>>ans;
	f_out.close();
	
	ifstream f_in(args[1]);
	f_in>>n;
	for(i=1;i<=n;i++){
		f_in>>x[i]>>y[i];
	}
	f_in.close();
	
	ifstream f_user(args[3]);
	if(!(f_user>>b) || b!=1){
		return wa;
	}
	for(i=2;i<=n+1;i++)if(!(f_user>>a) || a>n || a<=0 ||vis[a]){
		return wa;
	}else{
		vis[a]=1;
		tot+=getdis(a,b);
		b=a;
	}
	if(f_user>>a)return wa;
	f_user.close();
	if(tot>2LL*ans)return wa;
    return ac;  
}  
