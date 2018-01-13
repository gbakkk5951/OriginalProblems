using namespace std;
#include<fstream>
#define ac 0
#define wa 1
int n;
bool vis[5000010];

int main(int argc,char *args[])  
{
	int i,j,k;
	int a;
	ifstream f_in(args[1]);
	ifstream f_out(args[2]);
	ifstream f_user(args[3]);
	f_out.close();
	if(!(f_user>>a) || a!=1){
		return wa;
	}
	f_in>>n;
	f_in.close();
	for(i=2;i<=n+1;i++)if(!(f_user>>a) || a>n || a<=0 ||vis[a]){
		return wa;
	}else{
		vis[a]=1;
	}
	if(f_user>>a)return wa;
	f_user.close();
    return ac;  
}  
