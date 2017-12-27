using namespace std;
int main(){}
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
namespace Protector{
const long long llpow[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
const long long mod=(long long)1e9;
struct Bigint{
	typedef Bigint Big;
	long long num[250];
	int high;
	void zero(){
		memset(this,0,sizeof(Bigint));
	}
	Bigint(){
		zero();
	}
	Bigint(const Bigint &a){
		memcpy(this,&a,sizeof(Bigint));
	}
	
	
	template<typename Type>
	Bigint(Type a){
		*this=toBig(a);
	}	

	Bigint toBig (char *a){
		int len;
		int i;
		Big ans;
		for(len=0;*a;a++,len++);
		len--;
		for(i=0;i<=len;i++){
			a--;
			ans.num[i/9]+=(*a-'0')*llpow[i%9];
		}
		ans.gethigh((len+8)/9);
		return ans;
	}

	template<typename Type>
	Bigint toBig(Type a){
		Bigint ans;
		ans[0]=a%mod;
		ans[1]=a/mod%mod;
		ans[2]=a/mod/mod;
		ans.gethigh(2);
		return ans;
	}


	void gethigh(int mx=800){
		int i;
		high=0;
		for(i=mx;i;i--){
			if(num[i]){
				high=i;
				return;
			}
		}
	}
	
	void inline jinwei(int idx){
		if(num[idx]>=0){
			num[idx+1]+=num[idx]/mod;
			num[idx]%=mod;			
		}else{
			long long t=(num[idx]-mod+1)/mod;
			num[idx+1]+=t;
			num[idx]-=t*mod;
		}
	}
	
	inline long long & operator [] (int a){
		return num[a];
	}

		
		
	Bigint operator + (Bigint b){
		int i;
		Big ans(*this);
		for(i=0;i<=b.high|| i<=b.high;i++){
			ans[i]+=b[i];
			ans.jinwei(i);
		}	
		ans.gethigh(max(ans.high,b.high)+1);
		return ans;
	}
	
	Bigint operator - (){
		int i;
		Big ans(*this);
		for(i=0;i<=ans.high;i++){
			ans[i]=-ans[i];
		}
		return ans;
	}
		
	inline Bigint operator - (Bigint b){
		return *this+(-b);
	}
	Bigint operator * (Bigint b){
		Bigint ans;
		int i,j;
		for(i=0;i<=this->high;i++){
			for(j=0;j<=b.high;j++){
				ans.jinwei(i+j);
				ans[i+j]+=(*this)[i]*b[j];
				ans.jinwei(i+j);
			}
		}
		ans.gethigh((*this).high+b.high+1);
		return ans;
	}


	Bigint operator / (Bigint b){
		Bigint ans;
		Bigint a=*this,tmp;
		long long l,r,mid;
		int mxbit;
		if(a<b){
			return ans;
		}
		mxbit=a.high-b.high;

		int i;
		for(i=mxbit;i>=0;i--){
			l=0;r=mod-1;

			while(l<r){
				mid=(l+r)>>1;
				tmp[i]=mid+1;
				tmp.high=i;
				if(b*tmp<=a){
					l=mid+1;
				}else{	
					r=mid;
				}
			}
			tmp[i]=l;
			a-=b*tmp;
			tmp[i]=0;	
			ans[i]=l;
		}
		ans.gethigh(mxbit);
		return ans;
	}
	inline Bigint operator % (Bigint b){
		return *this-*this/b*b;
	}	
	
	bool operator == (Bigint b){
		Bigint a = *this;
		int i;
		if(a.high==b.high){
			for(i=0;i<=a.high;i++){
				if(a[i]!=b[i]){
					return false;
				}
			}
			return true;
		}else{
			return false;
		}
	}	
	bool operator < (Bigint b){
		Bigint a = *this;
		if(a.high!=b.high){
			if( a.num[a.high]<0 && a.num[a.high]<0 ){
				return a.high>b.high;
			}else if(a.num[a.high]>=0 && a.num[a.high]>=0){
				return a.high<b.high;
			}else{
				return a.num[a.high]<b.num[b.high];
			}
		}else{
			int i;
			for(i=a.high;i>=0;i--){
				if(a[i]!=b[i]){
					return a[i]<b[i];
				}
			}
			return false;
		}
	}
	inline bool operator > (Bigint b){
		return !(*this<=b);
	}	
	inline bool operator <= (Bigint b){
		return *this<b || *this==b;
	}		
	inline bool operator >= (Bigint b){
		return !(*this<b);
	}	
	inline bool  operator != (Bigint b){
		return !(*this==b);
	}		
	template<typename Type>
	inline Bigint operator -= (Type b){
		return *this=*this-b;
	}
	template<typename Type>
	inline Bigint operator += (Type b){
		return *this=*this+b;
	}
	template<typename Type>
	inline Bigint operator /= (Type b){
		return *this=*this/b;
	}	
	template<typename Type>
	inline Bigint operator *= (Type b){
		return *this=*this*b;
	}	
	template<typename Type>
	inline Bigint operator %= (Type b){
		return *this=*this%b;
	}		

	template<typename Type>
	inline Bigint operator + (Type b){
		return *this+toBig(b);
	}

	template<typename Type>
	inline Bigint operator - (Type b){
		return *this-toBig(b);
	}
	template<typename Type>
	inline Bigint operator * (Type b){
		return *this*toBig(b);
	}
	template<typename Type>
	inline Bigint operator / (Type b){
		return *this/toBig(b);
	}
	template<typename Type>
	inline Bigint operator % (Type b){
		return *this%toBig(b);
	}		
	
	template<typename Type>
	inline bool friend operator < (Bigint a,Type b){
		return a<a.toBig(b);
	}	
	template<typename Type>
	inline  bool friend operator > (Bigint a,Type b){
		return a>a.toBig(b);
	}		
	template<typename Type>
	inline  bool friend operator == (Bigint a,Type b){
		return a==a.toBig(b);
	}	
	template<typename Type>
	inline  bool operator != (Type b){
		return *this!=toBig(b);
	}		
	template<typename Type>
	inline  bool friend operator >= (Bigint a,Type b){
		return a>=a.toBig(b);
	}	
	template<typename Type>
	inline  bool friend operator <= (Bigint a,Type b){
		return a<=a.toBig(b);
	}
	
	template<typename Type>
	inline Bigint friend operator + (Type a,Bigint b){
		return toBig(a)+b;
	}
	template<typename Type>
	inline Bigint friend operator - (Type a,Bigint b){
		return toBig(a)-b;
	}
	template<typename Type>
	inline Bigint friend operator * (Type a,Bigint b){
		return toBig(a)*b;
	}	
	template<typename Type>
	inline Bigint friend operator / (Type a,Bigint b){
		return toBig(a)/b;
	}	
	template<typename Type>
	inline Bigint friend operator % (Type a,Bigint b){
		return toBig(a)%b;
	}	
	template<typename Type>
	inline  bool friend operator < (Type a,Bigint b){
		return toBig(a)<b;
	}	
	template<typename Type>
	inline  bool friend operator > (Type a,Bigint b){
		return toBig(a)>b;
	}		
	template<typename Type>
	inline  bool friend operator == (Type a,Bigint b){
		return toBig(a)==b;
	}	
	template<typename Type>
	inline  bool friend operator >= (Type a,Bigint b){
		return toBig(a)>=b;
	}	
	template<typename Type>
	inline  bool friend operator <= (Type a,Bigint b){
		return toBig(a)<=b;
	}	
	

					
	
	void print(int newline=false){
		int i;
		
		for(i=0;i<=high;i++){
			jinwei(i);
		}
		gethigh(high+1);
		printf("%lld",num[high]);
		for(i=high-1;i>=0;i--){
			printf("%09lld",num[i]);
		}
		if(newline)putchar('\n');
	}
};

Bigint gcd(Bigint a,Bigint b){
	Bigint t;
	while((t=a%b)>0){
		a=b;b=t;
	}
	return b;
}
Bigint pow[505];
struct Bigfrac{
public:	
	typedef Bigfrac Big;
	Bigint fz,fm;
	Bigfrac(){
		fz=0;fm=1;
	}
	Big friend operator + (Big a,Big b){
		Big ret;
		ret.fm=a.fm*b.fm;
		ret.fz=a.fz*b.fm+b.fz*a.fm;
		return ret;
	}
	Big operator += (Big b){
		return *this=*this+b;
	}
	void simplify(){
		if(fz!=0){
			Bigint tmp=gcd(fz,fm);
			fz/=tmp;fm/=tmp;		
		}else{
			fm=1;
		}
	}

	
};


bool Hezero(char *a){
	for( ;*a;a++){
		if(isdigit(*a) && *a!='0')return true;
	}
	return false;
}

struct _Main{
	typedef Bigfrac BigFrac;
	char lim[11][510],inf[11][510];
	int n;
	Bigint ans;
	BigFrac rate,tmp;
	_Main(){
//		freopen("test.out","w",stdout);
		int i,j,k;
		int la,lb;
		scanf("%d",&n);
		for(i=1;i<=n;i++){
			scanf("%s",lim[i]);
			if(lim[i][0]=='1'){
				printf("1");
				goto EndMain;
			}
			scanf("%s",inf[i]);
			if(!(Hezero(lim[i])||Hezero(inf[i]))){
				n--;i--;
			}
		}
		pow[0]=1;
		for(i=1;i<=500;i++){
			pow[i]=pow[i-1]*10;
		}
		ans=1;
		for(i=1;i<=n;i++){
			la=strlen(lim[i]+2);
			lb=strlen(inf[i]);
			rate.fz=lim[i]+2;
			rate.fm=pow[la];		
			tmp.fz=inf[i];
			tmp.fm=(pow[lb]-1)*pow[la];
			rate+=tmp;			
			rate.simplify();
			ans=ans/gcd(ans,rate.fm)*rate.fm;
		}
		ans.print();
		EndMain:
			fclose(stdout);
	}
	
	
}agriculture;



}
