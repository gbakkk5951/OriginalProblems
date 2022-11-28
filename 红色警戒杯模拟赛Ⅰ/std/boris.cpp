using namespace std;
int main(){}
#include<cstdio>
#include<set>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
const double eps=1e-6;
struct kind{
    string name;
    long long atk;long long hp;long long cnt; 
struct namecmp{
    bool inline operator () (const kind &a,const kind &b) {
        return a.name<b.name;
    }   
};
struct atkcmp{
    bool inline operator () (const kind &a,const kind &b) {
        return a.atk<b.atk;
    }
};
}enemy[5010],killing[25];
int knum;
long long dp[2100050];
double a,b,c,delta,mid;
long long sumatk;
struct _Main{
template<typename Type>
    void read(Type &a){
        char t,f=1;
        while(!isdigit(t=getchar())){
            if(t=='-')f=-1;
        }
        a=t-'0';
        while( isdigit(t=getchar())){
            a*=10;
            a+=t-'0';
        }a*=f;
    }
int num,kinds;long long hp,atk,hpadd;
long long addpersec;
_Main(){
	freopen("boris.out","w",stdout);
    freopen("boris.in","r",stdin);
    int i;long long othersum,allatk,temp;int I;
    read(kinds);read(num);read(hp);read(atk);read(hpadd);
    for(i=0;i<kinds;i++){
        cin>>enemy[i].name;
        read(enemy[i].hp);
        read(enemy[i].atk);
    }sort(enemy,enemy+kinds,kind::namecmp());
    for(i=0;i<num;i++){
        cin>>enemy[kinds].name;
        lower_bound(enemy,enemy+kinds,enemy[kinds],kind::namecmp())->cnt++;
    }
    for(i=0;i<kinds;i++){
        if(enemy[i].atk>0){
            killing[knum++]=enemy[i];
            swap(enemy[i],enemy[kinds-1]);
            i--;kinds--;
        }else{
            addpersec-=enemy[i].atk*enemy[i].cnt;
        }
    }
    dp[(1<<knum)-1]=hp+hpadd;
    for(i=0;i<knum;i++){
        dp[((1<<knum)-1)^(1<<i)]=hp;
    }
    long long t1;
    for(I=(1<<knum)-1;I>0;I--)if(dp[I]>0){
        for(i=0,othersum=0;i<knum;i++)if((I>>i)&1){
            othersum+=killing[i].atk *killing[i].cnt;
        }othersum-=addpersec;
        for(i=0;i<knum;i++)if((I>>i)&1){//枚举干掉哪个 
            allatk=othersum-killing[i].atk*killing[i].cnt;
            t1=(killing[i].hp+atk-1)/atk;//单个攻击次数 
            temp=killing[i].cnt*t1*allatk;
            temp+=killing[i].atk*(t1+t1*killing[i].cnt)*killing[i].cnt/2-killing[i].cnt*killing[i].atk;         
            if(temp>=dp[I])continue;
            if(t1==1){
                a=-killing[i].atk*t1;
                b=(killing[i].atk*t1+2*killing[i].atk-2*t1*allatk);
                c=killing[i].atk*t1*killing[i].cnt*(killing[i].cnt+1)-2*killing[i].cnt*killing[i].atk
                    -2*killing[i].atk+2*allatk*killing[i].cnt*t1+2*allatk*t1;               
            }else{
                a=-killing[i].atk*t1;
                b=(killing[i].atk*t1+2*killing[i].atk-2*t1*allatk) -killing[i].atk;
                c=killing[i].atk*t1*killing[i].cnt*(killing[i].cnt+1)-2*killing[i].cnt*killing[i].atk
                    -2*killing[i].atk+2*allatk*killing[i].cnt*t1+2*allatk*t1 +killing[i].atk-allatk;                    
            }
 
             
            mid=-b/(2*a);
            if(mid>killing[i].cnt){
                mid=killing[i].cnt;
            }else if(mid<1){
                mid=1;
            }
            if(fabs(floor(mid+eps)-mid)>eps){
                mid=floor(mid+eps);
                if(mid>=1 && mid<=killing[i].cnt){
                    if((mid*mid*a+b*mid+c)/2 > dp[I] -1+eps){
                        continue;
                    }
                }mid++;
                if(mid>=1 && mid<=killing[i].cnt){
                    if((mid*mid*a+b*mid+c)/2 > dp[I] -1+eps){
                        continue;
                    }   
                }                   
            }else{
                if((mid*mid*a+b*mid+c)/2 > dp[I] -1+eps){
                    continue;
                }                           
            }
            dp[I^(1<<i)]=max(dp[I^(1<<i)],dp[I]-temp);
        }
    }
     
    if(dp[0]<=0){
        printf("leave!");
        goto EndMain;
    }
    sort(enemy,enemy+kinds,kind::atkcmp());
    for(i=kinds-1;i>=0;i--){
        dp[0]+=enemy[i].cnt * ((enemy[i].hp+atk-1)/atk-1)*addpersec;
    }
    for(i=kinds-1;i>=0;i--){
        addpersec-=enemy[i].cnt*(-enemy[i].atk);
        dp[0]+=addpersec*enemy[i].cnt;
        dp[0]+=(-enemy[i].atk)*(0+enemy[i].cnt-1)*enemy[i].cnt/2;
    }
    printf("%lld",dp[0]);
    EndMain:
    fclose(stdout);
}   
     
     
     
     
     
}boris;

