//
//  main.cpp
//  sugar
//
//  Created by gengyf on 2019/7/9.
//  Copyright ? 2019 yifan Geng. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;
#define maxn 5000000+10
char str[maxn*2];
char s[maxn*2];
struct node{
    int fail;
    int cnt;
    int next[62];
}trie[maxn];
int k,ans;
queue<int>q;
void build_trie(int id,char *s){
    int len=strlen(s);
    int j=0;
    for(int i=0;i<len;i++){
        j=s[i]-'0';
        if(trie[id].next[j]==0){
            trie[id].next[j]=++k;
        }
        id=trie[id].next[j];
    }
    trie[id].cnt++;
}
void build_fail(int id){
    while(!q.empty())q.pop();
    for(int i=0;i<2;i++){
        int j=trie[id].next[i];
        if(j!=0){
            q.push(j);
            trie[j].fail=id;
        }
    }
    while(q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<2;i++){
            int j=trie[now].next[i];
            if(j==0){
                trie[now].next[i]=trie[trie[now].fail].next[i];
                continue;
            }
            trie[j].fail=trie[trie[now].fail].next[i];
            q.push(j);
        }
    }
}
void solve_trie(int id,char *s){
    int len=strlen(s);
    for(int i=0;i<len;i++){
        int j=trie[id].next[s[i]-'0'];
        while(j&&trie[j].cnt!=-1){
            ans+=trie[j].cnt;
            trie[j].cnt=-1;
            j=trie[j].fail;
        }
        id=trie[id].next[s[i]-'0'];
    }
}
int main(){
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
    int n;
    scanf("%d",&n);
    scanf("%s",s);
    build_trie(0,s);
    for(int i=1;i<=n;i++){
        scanf("%s",str);
        build_trie(0,str);
    }
    build_fail(0);
    solve_trie(0,s);
    printf("%d\n",ans);
    fclose(stdin);fclose(stdout);
    return 0;
}
