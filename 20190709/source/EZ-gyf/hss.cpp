//
//  main.cpp
//  hss
//
//  Created by gengyf on 2019/7/9.
//  Copyright ? 2019 yifan Geng. All rights reserved.
//

#include <bits/stdc++.h>
using namespace std;
int n,m,num;
char str[5010];
int ans;
bool flag=false;
stack<char>s;
int main() {
    freopen("hss.in", "r", stdin);
    freopen("hss.out", "w", stdout);
    scanf("%d%d",&n,&m);
    if(m!=0){
        return 0;
    }
    for(int i=1;i<=n;i++){
        scanf("%s",&str[i]);
        if(str[i]=='S'){
            num++;
        }
    }
    for(int i=1;i<=n;i++){
        if(str[i]=='s'){
            s.push(str[i]);
            flag=true;
        }
        if(str[i]=='h'&&s.size()!=0){
            s.pop();
            ans+=2;
        }
        if(str[i]=='S'){
            if(flag){
                ans++;
            }
        }
    }
    if(ans+num==n)printf("%d",n);
    else printf("%d",ans);
    fclose(stdin);fclose(stdout);
    return 0;
}
