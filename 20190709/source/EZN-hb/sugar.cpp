#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N=5000010;
struct kkk{
    int son[2],flag,fail;
}trie[N];
int n,cnt;
char s[N];
char a[N];
queue<int >q;
void insert(char* s){
    int u=1,len=strlen(s);
    for(int i=0;i<len;i++){
        int v=s[i]-'0';
        if(!trie[u].son[v])trie[u].son[v]=++cnt;
        u=trie[u].son[v];
    }
    trie[u].flag++;
}
void getFail(){
    for(int i=0;i<2;i++)trie[0].son[i]=1;          
    q.push(1);trie[1].fail=0;               
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<2;i++){              
            int v=trie[u].son[i];           
            int Fail=trie[u].fail;          
            if(!v){trie[u].son[i]=trie[Fail].son[i];continue;}  
            trie[v].fail=trie[Fail].son[i]; 
            q.push(v);                      
        }
    }
}
int query(char* s){
    int u=1,ans=0,len=strlen(s);
    for(int i=0;i<len;i++){
        int v=s[i]-'0';
        int k=trie[u].son[v];       
        while(k>1&&trie[k].flag!=-1){   
            ans+=trie[k].flag,trie[k].flag=-1;  
            k=trie[k].fail;         
        }
        u=trie[u].son[v];           
    }
    return ans;
}
int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
    cnt=1;scanf("%d",&n);
    scanf("%s",a);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        insert(s);
    }
    getFail();
    printf("%d\n",query(a));
    return 0;
}
