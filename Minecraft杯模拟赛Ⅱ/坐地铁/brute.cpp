using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<algorithm>
const long long mod=(long long)1e9+9;
struct _Main{
	template<typename Type>
		void read(Type &a){
			char t;
			while(!isdigit(t=getchar()));
			a=t-'0';
			while( isdigit(t=getchar())){
				a*=10;a+=t-'0';
			}
		}
	~_Main(){
		fclose(stdout);
	}
	long long n,mxcnt;
	long long arrtme[100005];
	long long arrnum[100005];
	long long mxtme[100005];
	long long num[100005];
	long long dis[100005];
	long long res;
	long long mxl,mxr,mxsum,mxdec;
	_Main(){
		long long i,j,k;bool flag;
		long long tme_tmp=0,num_tmp=0;
		long long l=1,r,sum,dec;
		read(n);read(mxcnt);
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
		flag=true;
//		flag=false;
		while(mxcnt>0 && flag){
			flag=false;
			mxsum=-1;
			l=1;
			while(l<n){
				sum=0;
				while(dis[l]==0){
					l++;
					if(l>=n)break;
				}
				if(l<n){
					r=l+1;
					dec=dis[l];
					dec=min(dis[l],mxcnt);
					while(r<n && arrtme[r]-mxtme[r]>0){
						sum+=arrnum[r];
						dec=min(dec,arrtme[r]-mxtme[r]);
						r++;
					}
					sum+=arrnum[r];
					if(dec>0 &&sum>mxsum){
						mxsum=sum;
						mxl=l;
						mxr=r;
						mxdec=dec;
					}
					l=r;
				}
			}
			if(mxsum>0){
				flag=true;
				mxcnt-=mxdec;
				dis[mxl]-=mxdec;
				for(i=mxl+1;i<=mxr;i++){
					arrtme[i]-=mxdec;
				}
//				printf("[%lld,%lld]-=%lld\n",mxl,mxr,mxdec);
			}
		}
		res=0;
		for(i=2;i<=n;i++){
			(res+=arrtme[i]%mod*(arrnum[i]%mod) )%=mod;
		}
		for(i=1;i<=n-1;i++){
			(res+=-((long long) n-i)*mxtme[i]%mod*num[i]%mod)%=mod;
		}
		printf("%lld",(res%mod+mod)%mod);		
	}
	
	
	
	
	
	
	
	
	
	
	
	
}brute;
