using namespace std;
int main(){}
#include<cstdio>
#include<iostream>
#include<cctype>
#include<map>
#include<string>
#include<cstring>
map<string,int> mmp;
int n,m;
int mmpcnt;
struct BlossomTree{

private:
	int matchcnt;
	int start,finish;
	bool Glink[305][305];
	bool inq[305],inbl[305];
	int path[305];
	int match[305],fa[305];
	int base[305];
	int q[305];
	int newbase;
	int pathcnt;
	
	
	int tail,head;
	int pop(){
		return q[head++];
	}
	void push(int a){
		inq[a]=1;
		q[tail++]=a;
	}
	int GetLCA(int u,int v){
		for(++pathcnt;;swap(u,v)){
			u=base[u];
			if(path[u]==pathcnt)return u;
			path[u]=pathcnt;
			u=fa[match[u]];
		}
	}
	void ResetTrace(int u){
		int v;
		while(base[u]!=newbase){
			v=match[u];
			inbl[base[u]]=inbl[base[v]]=1;
			u=fa[v];
			if(base[u]!=newbase)fa[u]=v;
		}
	}
	void ContractBlossom(int u,int v){
		memset(inbl,0,sizeof(inbl));
		newbase=GetLCA(u,v);
		ResetTrace(u);
		ResetTrace(v);
		if(base[u]!=newbase)fa[u]=v;
		if(base[v]!=newbase)fa[v]=u;
		int tu;
		for(tu=1;tu<=n;tu++){
			if(inbl[base[tu]]){
				base[tu]=newbase;
				if(!inq[tu])push(tu);
			}
		}
	}
	void ResetBase(){
		int u;
		for(u=1;u<=n;u++){
			base[u]=u;
		}
	}
	void FindAugmentingPath(){
		memset(fa,0,sizeof(fa));
		memset(inq,0,sizeof(inq));
		ResetBase();
		finish=0;
		head=tail=0;
		push(start);
		int u,v;
		while(head<tail){
			u=pop();
			for(v=1;v<=n;v++){
				if(Glink[u][v] && base[u]!=base[v] &&match[u]!=v){
					if(v==start || (match[v] && fa[match[v]])){
						ContractBlossom(u,v);
					}else if(fa[v]==0){
						fa[v]=u;
						if(match[v]){
							push(match[v]);
						}else{
							finish=v;
							return;
						}
					}
				}
			}
		}
	}
	void AugmentPath(){
		int u,v,w;
		u=finish;
		while(u){
			v=fa[u];
			w=match[v];
			match[v]=u;
			match[u]=v;
			u=w;
		}
	}
	
	
public:
	void add(int a,int b){
		Glink[a][b]=Glink[b][a]=1;
	}
	int Edmonds(){
		int u;
		memset(match,0,sizeof(match));
		for(u=1;u<=n;u++){
			if(!match[u]){
				start=u;
				FindAugmentingPath();
				if(finish){
					AugmentPath();
					matchcnt++;
				}
			}
		}
		return count();
	}	
	int inline count(){
		return matchcnt;
	}
	
}matcher;
	
struct _Main{


string a,b;
_Main(){
	map<string,int>::iterator it;
	std::ios::sync_with_stdio(false);
	cin>>n>>m;
	int i;int idxa,idxb;
	for(i=1;i<=m;i++){
		cin>>a>>b;
		if((it=mmp.find(a))!=mmp.end()){
			idxa=it->second;
		}else{
			idxa=mmp[a]=++mmpcnt;
		}
		if((it=mmp.find(b))!=mmp.end()){
			idxb=it->second;
		}else{
			idxb=mmp[b]=++mmpcnt;
		}
		matcher.add(idxa,idxb);
	}
	cout<<matcher.Edmonds()*2<<endl;
}	
	
	
	
	
}chaosdrone;	
