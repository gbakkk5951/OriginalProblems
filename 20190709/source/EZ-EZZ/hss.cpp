#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
queue<int> q;
int main(){
    freopen("hss.in","r",stdin);
    freopen("hss.out","w",stdout);
    char c[10000];int n,m;
    scanf("%d%d",&n,&m);q.push(667729894);
    for(register int i=1;i<=n;i++)
    scanf("%s",&c[i]);
    for(register int i=1;i<=n;i++){
        if(c[i]=='s'||c[i]=='S') q.push(i);
        else{
            int how=q.front();
            if(how==667729894) continue;
            else q.pop();
        }
    }
    printf("%d",n-q.size()-1);
    return 0;
}
