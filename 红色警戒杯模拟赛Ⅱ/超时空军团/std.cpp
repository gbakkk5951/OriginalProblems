using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>
int n,m,ndcnt;             
long long mod;
                         
struct SubSumTree{
	int base;
	vector<int>node;
	void resize(int a){
		int i;
		for(i=0;(1<<i)<(a+2);i++);
		base=(1<<i);
		node.resize(base*2+5);
	}
	void add(int s,int val){
		for(s=s+base;s;s>>=1){
			node[s]+=val;
		}
	}
	int query(int s,int t){
		int ans=0;
		for(s=s+base-1,t=t+base+1;s^t^1;s>>=1,t>>=1){
			if(~s&1)ans+=node[s^1];
			if( t&1)ans+=node[t^1];
		}
		return ans;
	}
};
struct SumTree{
	int base;
	vector<SubSumTree>node;
	void resize(int a,int b){
		int i;
		for(i=0;(1<<i)<(a+2);i++);
		base=(1<<i);
		node.resize(base*2+5);
		for(i=1;i<=(base<<1);i++){
			node[i].resize(b);
		}
	}
	void change(int s,int y,int val){
		for(s=s+base;s;s>>=1){
			node[s].add(y,val);
		}
	}
	int query(int s,int t,int y1,int y2){
		s=max(s,1);t=min(t,n);
		y1=max(y1,1);y2=min(y2,m);
		int ans=0;
		for(s=s+base-1,t=t+base+1;s^t^1;s>>=1,t>>=1){
			if(~s&1)ans+=node[s^1].query(y1,y2);
			if( t&1)ans+=node[t^1].query(y1,y2);
		}
		return ans;
	}
}sumtree;

struct SubMaxTree{
	int base;
	vector<int>node;
	void resize(int a){
		int i;
		for(i=0;(1<<i)<(a+2);i++);
		base=(1<<i);
		node.resize(base*2+5);
	}
	void change(int s,int val){
		for(s=s+base;s&&node[s]<val;s>>=1){
			node[s]=val;
		}
	}
	int query(int s,int t){

		int ans=0;
		for(s=s+base-1,t=t+base+1;s^t^1;s>>=1,t>>=1){
			if(~s&1)ans=max(ans,node[s^1]);
			if( t&1)ans=max(ans,node[t^1]);
		}
		return ans;
	}
};
int link[205][205];
int degree[205];
struct MaxTree{
	int base;
	vector<SubMaxTree>node;
	void resize(int a,int b){
		int i;
		for(i=0;(1<<i)<(a+2);i++);
		base=(1<<i);
		node.resize(base*2+5);
		for(i=1;i<=(base<<1);i++){
			node[i].resize(b);
		}
	}
	void change(int s,int y,int val){
		for(s=s+base;s;s>>=1){
			node[s].change(y,val);
		}
	}
	int query(int s,int t,int y1,int y2){
		s=max(s,1);t=min(t,n);
		y1=max(y1,1);y2=min(y2,m);
		int ans=0;
		for(s=s+base-1,t=t+base+1;s^t^1;s>>=1,t>>=1){
			if(~s&1)ans=max(ans,node[s^1].query(y1,y2));
			if( t&1)ans=max(ans,node[t^1].query(y1,y2));
		}
		return ans;
	}
}mxtree;


struct _Main{
long long *matrix[205];
void gause(){
	int i,j,k;long long times;
	for(i=1;i<=ndcnt-2;i++){
		for(j=i;j<=ndcnt;j++){
			if(matrix[i][j])break;
		}
		swap(matrix[i],matrix[j]);
		for(j=i+1;j<=ndcnt-1;j++)while(matrix[j][i]){
			if(matrix[i][i]==0){
				swap(matrix[i],matrix[j]);
				continue;
			}
			if(abs(matrix[i][i])>=abs(matrix[j][i])){
				times=matrix[i][i]/matrix[j][i];
				for(k=i;k<=ndcnt-1;k++){
					matrix[i][k]-=matrix[j][k]*times%mod;
					matrix[i][k]%=mod;
				}
			}else{
				times=matrix[j][i]/matrix[i][i];
				for(k=i;k<=ndcnt-1;k++){
					matrix[j][k]-=matrix[i][k]*times%mod;
					matrix[j][k]%=mod;
				}
			}
		}
	}
}
vector<int>info[205];	
	
long long  org[205][205];
template<typename Type>
	void read(Type &a){
		char t;
		while(!isdigit(t=getchar()));
		a=t-'0';
		while( isdigit(t=getchar())){
			a*=10;a+=t-'0';
		}
	}
long long age[205];
long long sorted[205];
int ecnt;
_Main(){
	int i,j,k;int a,b,c,d;int l,r,mid;int temp;
	long long ans;
	read(n);read(m);read(ndcnt);read(mod);
	sumtree.resize(n,m);
	mxtree.resize(n,m);
	for(i=1;i<=ndcnt;i++){
		matrix[i]=org[i];
	}
	
	for(i=1;i<=ndcnt;i++){
		read(a);read(b);read(c);read(d);
		info[i].resize(d+2);
		sorted[i]=age[i]=c;
		info[i][0]=a;info[i][1]=b;
		for(j=0;j<d;j++){
			read(a);
			info[i][2+j]=a;
		}
		sort(info[i].begin()+2,info[i].begin()+2+d);
	}
	sort(sorted+1,sorted+1+ndcnt);
	for(i=1;i<=ndcnt;i++){
		age[i]=lower_bound(sorted+1,sorted+1+ndcnt,age[i])-sorted;
		mxtree.change(info[i][0],info[i][1],age[i]);
		sumtree.change(info[i][0],info[i][1],1);
	}
	for(i=1;i<=ndcnt;i++){
		l=1;
		for(j=2;j<info[i].size();j++){
			r=max(max(abs(n-info[i][0]),info[i][0]),max(abs(m-info[i][1]),info[i][1]));
			while(l<r){
				mid=(l+r)>>1;
				temp=sumtree.query(info[i][0]-mid,info[i][0]+mid,info[i][1]-mid,info[i][1]+mid);
				if(temp>info[i][j]){
					r=mid;
				}else if(temp==info[i][j]){
					l=r=mid;
				}else{
					l=mid+1;
				}
			}
			temp=mxtree.query(info[i][0]-l,info[i][0]+l,info[i][1]-l,info[i][1]+l);
			if(temp!=age[i] && !link[temp][age[i]]){
				link[temp][age[i]]=link[age[i]][temp]=1;
				degree[temp]++;
				degree[age[i]]++;
				ecnt++;
			}
		}
	}
	for(i=1;i<=ndcnt;i++){
		for(j=1;j<=ndcnt;j++){
			if(i==j){
				matrix[i][j]=degree[i];
			}else{
				matrix[i][j]-=link[i][j];
			}
		}
	}
	gause();
	for(i=1,ans=1;i<=ndcnt-1;i++){
		ans=ans*matrix[i][i]%mod;
	}
	for(i=1;i<=(ecnt-(ndcnt-1));i++){
		ans=ans*i%mod;
	}
	
	printf("%lld",(ans%mod+mod)%mod);
	fclose(stdout);
}
	
	
}chrono;
