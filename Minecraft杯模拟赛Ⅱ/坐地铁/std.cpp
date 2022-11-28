using namespace std;
int main(){}
#include<algorithm>
#include<cstdio>
#include<cctype>
#include<queue>
#include<iostream>

const long long mod=(long long )1e9+9;

struct Lson{
	int inline  operator [] (int a){
		return a<<1;
	}
}lson;
struct Rson{
	int inline  operator [] (int a){
		return a<<1|1;
	}
}rson;
struct Range{
	int l;int r;
	long long sum;
	bool friend operator < (const Range &a,const Range &b){
		return a.sum<b.sum;
	}
};


long long n;	
struct _Main{
	
priority_queue<Range>heap;
long long mxcount;	
long long node[270000];//最小的Arrtime - Mxtime 
long long sig[270000];
int l[270000],r[270000];
int arr[100010],arridx;
long long dis[100005];
long long arrnum[100005];
long long arrtme[100010],num[100010];
long long arrtme_[100010];
long long mxtme[100010];
long long numsum[100005];
void initree(int nd=1){
	if(l[nd]==r[nd]){
		node[nd]=arrtme[l[nd]]-mxtme[l[nd]];
		return;
	}
	initree(lson[nd]);
	initree(rson[nd]);
	node[nd]=min(node[lson[nd]],node[rson[nd]]);
}

void push(int nd){
	if(sig[nd]){
		sig[lson[nd]]+=sig[nd];
		sig[rson[nd]]+=sig[nd];
		node[lson[nd]]+=sig[nd];
		node[rson[nd]]+=sig[nd];		
		sig[nd]=0;
	}
	
}
void getrange(int nd=1,int ql=1,int qr=n){
	l[nd]=ql;r[nd]=qr;
	if(ql!=qr){
		getrange(lson[nd],ql,(ql+qr)>>1);
		getrange(rson[nd],((ql+qr)>>1)+1,qr);
	}
}

void change(int ql,int qr,int val,int nd=1){
	if(l[nd]>qr ||r[nd]<ql)return;
	if(ql<=l[nd] && r[nd]<=qr){
		sig[nd]+=val;
		node[nd]+=val;
		return;
	}
	push(nd);
	change(ql,qr,val,lson[nd]);
	change(ql,qr,val,rson[nd]);
	node[nd]=min(node[lson[nd]],node[rson[nd]]);
}
long long querymin(int ql,int qr,int nd=1){
	if(l[nd]>qr ||r[nd]<ql)return 1e18;
	
	if(ql<=l[nd] && r[nd]<=qr){
		return	node[nd];
	}
	push(nd);
	return min(querymin(ql,qr,lson[nd]),querymin(ql,qr,rson[nd]));
}

void querynode(int ql,int qr,int nd=1){
	if(l[nd]>qr ||r[nd]<ql || node[nd]>0)return;
	if(l[nd]==r[nd]){
		arr[arridx++]=l[nd];
		return;
	}
	push(nd);
	querynode(ql,qr,lson[nd]);
	querynode(ql,qr,rson[nd]);
}
void insert(){
	int i;Range tmp;
	int l=-1,r;
	
	l=arr[0];
	for(i=0;i<arridx-1;){
		while(dis[l]==0){
			l++;
			if(l==arr[arridx-1])goto EndFunc;
			if(l==arr[i+1])i++;
			if(i==arridx-1)goto EndFunc;
		}
		i++;
		r=arr[i];
		heap.push((Range){l,r,numsum[r]-numsum[l]});/*不能加if(l<r-1)*/
		l=r;
	}
	EndFunc:
	arridx=0;
}

	template<typename Type>
		void read(Type &a){
			char t;
			while(!isdigit(t=getchar()));
			a=t-'0';
			while( isdigit(t=getchar())){
				a*=10;a+=t-'0';
			}
		}

	_Main(){
		int i;
		long long tme_tmp=0,num_tmp=0;
		long long res=0;
		read(n);read(mxcount);
		for(i=1;i<=n;i++){
			arrnum[i]=num_tmp;
			arrtme[i]=tme_tmp;
			if(i!=n){
				read(num[i]);
				read(mxtme[i]);
				read(dis[i]);
				num_tmp+=num[i];
				tme_tmp=max(tme_tmp,mxtme[i])+dis[i];	
			}
		}
		for(i=2;i<=n;i++){
			arrnum[i]=arrnum[i-1]+num[i-1];
		}
		
		for(i=2;i<=n;i++){
			numsum[i]=numsum[i-1]+arrnum[i];
		}
		getrange();
		initree();
		arr[arridx++]=1;
		if(n>=3)querynode(2,n-1);
		arr[arridx++]=n;
		insert();
		solve();
		res=0;
		for(i=2;i<=n;i++){
			(res+=arrtme[i]%mod*(arrnum[i]%mod) )%=mod;
		}
		for(i=1;i<=n-1;i++){
			(res+=-((long long) n-i)*mxtme[i]%mod*num[i]%mod)%=mod;
		}
		printf("%lld",(res%mod+mod)%mod);
	}
	
	void solve(){
		Range nd;
		long long dec;
		int i;
		while(mxcount>0 && !heap.empty() && heap.top().sum>0){
			nd=heap.top();
			heap.pop();
			dec=min(mxcount,dis[nd.l]);
			if(nd.l<nd.r-1)dec=min(dec,querymin(nd.l+1,nd.r-1));
			mxcount-=dec;
			dis[nd.l]-=dec;
			change(nd.l+1,nd.r,-dec);
			arrtme_[nd.l+1]-=dec;arrtme_[nd.r+1]+=dec;
			if(nd.l<nd.r-1){
				arr[arridx++]=nd.l;
				if(nd.l+1<nd.r)querynode(nd.l+1,nd.r-1);
				arr[arridx++]=nd.r;
				insert();
			}
		}
		for(i=1;i<=n;i++){
			arrtme_[i]+=arrtme_[i-1];
			arrtme[i]+=arrtme_[i];
		}
	}
	
}subwayI;
