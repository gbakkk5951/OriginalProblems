#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int n;
char s[5000010];
char nows[5000010];
int f[5000010];
queue<int>q;
int tot=0;
struct node{
	int len;
	int end;
	int son[2];
	int fail;
}trie[5000010];
void insert(char *a){
	int len=strlen(a);
	int now=0;
	for(int i=0;i<len;i++){
		int c=a[i]-'0';
		if(!trie[now].son[c])trie[now].son[c]=++tot;
		now=trie[now].son[c];
	}
	trie[now].end=1;
	trie[now].len=len;
}
void getfail(){
	trie[0].fail=0;
	for(int i=0;i<2;i++){
		if(trie[0].son[i]){
			trie[trie[0].son[i]].fail=0;
			q.push(trie[0].son[i]);
		}
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<2;i++){
			if(trie[x].son[i]){
				trie[trie[x].son[i]].fail=trie[trie[x].fail].son[i];
				q.push(trie[x].son[i]);
			}
			else trie[x].son[i]=trie[trie[x].fail].son[i];
		}
	}
}
void solve(char *a){
	int len=strlen(a);
	int now=0;
	for(int i=0;i<len;i++){
		int c=a[i]-'0';
		now=trie[now].son[c];
		for(int t=now;t;t=trie[t].fail){
		//	cout<<"#"<<i+1<<" "<<f[i+1]<<" "<<i-trie[t].len+1<<" "<<f[i-trie[t].len+1]<<endl;
			if(trie[t].end)f[i+1]=max(f[i+1],f[i-trie[t].len+1]+1);
		}
		f[i+1]=max(f[i+1],f[i]);
	//	cout<<"#"<<i+1<<" "<<f[i+1]<<endl;
	}
}
int main(){
//	freopen("input.in","r",stdin);
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	memset(f,0,sizeof(f));
	scanf("%d",&n);
	scanf("%s",s);
	for(int i=1;i<=n;i++){
		scanf("%s",nows);
		insert(nows);
	}
	getfail();
	f[0]=0;
	solve(s);
	printf("%d\n",f[strlen(s)]);
	return 0;
}
