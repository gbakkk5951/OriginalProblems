#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=5000009;
int n,tot;
int trie[maxn][2];
int cnt[maxn],fail[maxn];
char s[maxn],ch[maxn];
void insert(char *s){
	int x=0,l=strlen(s);
	for(int i=0;i<l;i++){
		int c=s[i]-'0';
		if(!trie[x][c])trie[x][c]=++tot;
		x=trie[x][c];
	}
	cnt[x]++;
}
void getfail(){
	queue<int>q;
	for(int i=0;i<=1;i++){
		if(trie[0][i]){
			fail[trie[0][i]]=0;
			q.push(trie[0][i]);
		}
	}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<=1;i++){
			if(trie[x][i]){
				fail[trie[x][i]]=trie[fail[x]][i];
				q.push(trie[x][i]);
			}
			else trie[x][i]=trie[fail[x]][i];
		}
	}
}
int query(char *s){
	int x=0,ans=0,l=strlen(s);
	for(int i=0;i<l;i++){
		int c=s[i]-'0';
		x=trie[x][c];
		for(int j=x;j;j=fail[j]){
//			ans+=cnt[j];
			if(cnt[j]){
				ans++;x=0;break;
			}
		}
	}
	return ans;
}
int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",ch);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		insert(s);
	}
	fail[0]=0;
	getfail();
	printf("%d\n",query(ch));
}
