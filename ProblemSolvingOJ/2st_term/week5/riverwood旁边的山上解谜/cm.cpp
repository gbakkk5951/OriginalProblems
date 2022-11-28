using namespace std;
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<fstream>
#include <vector>
#include <sys/time.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
//#include "splay.hpp"
typedef long long lld;
struct _Main{
//////////////
string dataName = "data";
string stdName = "std";
string bruteName = "brute";
bool make_data = 1;
bool run_ans = 1;

lld srand_seed = 0;

int beg = 0
,   end = 0//26
,   exbeg = 0
,   exend = 10
;

bool check_brute = 0;
bool check_out_pause = true;
bool loop_check = 0;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

//Splay<400005>leaf, id, void_id;
void make(){
	for(int I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		/*
		max:
		AA 最后1位很大，前面都小于一半
		A 存在和 >= scale // 卡个 等于？
		B 不存在 >= scale
		
		min:
		C 存在前导0，且首位 + x < scale 的最大x位置 > 2
		CC 第二位是0,后面的 + 首尾 均大于零
		DD 最后1位很小，前面的都是 > 1 / 2的
		D 存在不进位的和
		E 不存在不进位的和
		
		
		随机
		*/
		int n, k;
		int Base = 13;
		if (I < Base) {
			n = lrand(5,11);
			k = lrand(11, 21);
		}
		else
		if (I < Base * 2) {
			n = 1e6;
			k = 1e9;
		}
		int type = I % Base;
		if (type >= 11) {
			k = n + 1;
		}
		cout << n << sp << k << endl;
		if (type == 0) {//随机
			cout << lrand(1, k - 1) << sp;
			for (int i = 2; i <= n; ++i) {
				cout << lrand(0, k - 1) << sp;
			}
		} else 
		if (type == 1) {// AA 最后1位很大，前面都小于一半
			cout << lrand(1, (k - 1) / 2) << sp;
			for (int i = 2; i <= n - 1; ++i) {
				cout << lrand(0, (k - 1) / 2) << sp;
			}
			cout << (k - 1);
		} else 
		if (type == 2) { // A 存在和 > scale 
			cout << (k - 2) << sp << (k - 1) << sp;
			for (int i = 3; i <= n; ++i) {
				cout << lrand(0, (k - 2) / 2) << sp;
			}
		} else 
		if (type == 3) {
		//B 不存在 >= scale
			cout << lrand(1, (k - 2) / 2) << sp;
			for (int i = 2; i <= n; ++i) {
				cout << lrand(0, (k - 2) / 2) << sp;
			}
		} else 
		if (type == 4) {
		//C 存在前导0，且首位 + x < scale 的最大x位置 > 2
			cout << lrand(1, (k - 2) / 2) << sp << 0 << sp;
			int bit = lrand(3, n - 3);
			for (int i = 3; i <= bit; ++i) {
				cout << 0 << sp;
			}
			for (int i = bit + 1; i <= n; ++i) {
				cout << lrand(0, (k - 1)) << sp;
			}
		} else 
		if (type == 5) {
		//CC 第二位是0,后面的 + 首位 均大于k
			cout << (k - 2) << sp << 0 << sp;
			for (int i = 3; i <= n; ++i) {
				cout << lrand(2, k - 1) << sp;
			}
		} else 
		if (type == 6) {
		//DD 最后1位很小，前面的都是 > 1 / 2的
			cout << (k - 1) << sp;
			for (int i = 2; i <= n - 1; ++i) {
				cout << lrand((k / 2) + 1, k - 1) << sp;
			}
			cout << 0 << sp;
		} else 
		if (type == 7) {
		//D 存在不进位的和
			int l, r;
//			randRange(2, n - 1, l, r);
			l = lrand(2, n / 4);
			r = lrand(n / 2, 2 * n / 3);
			for (int i = 1; i <= n; ++i) {
				if (i != l && i != r) {
					cout << lrand(min(k - 2, (k / 2) + 3), k - 1) << sp;
				} else {
					cout << (k - 1) / 2 << sp;
				}
			}
		} else 
		if (type == 8) {
		//E 不存在不进位的和
			for (int i = 1; i <= n; ++i) {
				cout << lrand((k / 2) + 1, k - 1) << sp;
			}
		} else 
		if (type == 9) {//最大和 == scale
			cout << ((k) / 2) << sp;
			int mid = lrand(2, n - 1);
			for (int i = 2; i <= n; ++i) {
				if (i == mid) {
					cout << ((k + 1) / 2) << sp;
				} else {
					cout << ((k) / 2) << sp;
				}
			}
		} else
		if (type == 10) {// x 0 0 0 0 0 ... 0
			cout << lrand(1, k - 1) << sp;
			for (int i = 2; i <= n; ++i) {
				cout << 0 << sp;
			}
		} 
		else if (type == 11) {
			for (int i = 1; i <= n; ++i) {
				cout << i << sp;
			}
		} else
		if (type == 12) {
			for (int i = 1; i <= n; ++i) {
				cout << (n - i + 1) << sp;
			}
		}
		
		
		EndFor1:
		cout.close();
	}
	

	
	for(int I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int n, k;
		int type = I >> 1;
		n = (I & 1) ? 7 : 1e6;
		
		vector<int> arr;
		if (type == 0) {
			k = 2;
			for (int i = 1; i <= n; ++i) {
				arr.push_back((i <= 2 || (rand() & 1)));
			}
		} else
		if (type == 1) {
			k = 2;
			for (int i = 1; i <= n; ++i) {
				arr.push_back(1);
			}
		} else 
		if (type == 2) {
			k = lrand(1e8, 1e9);
			for (int i = 1; i <= n; ++i) {
				arr.push_back(i == 1 ? 1 : k - 1);
			}
		}
		if (type == 3) {
			k = lrand(1e8, 1e9 - 1);
			k |= 1;
			for (int i = 1; i <= n; ++i) {
				arr.push_back(i == 1 ? (k >> 1) : ((k >> 1) + 1));
			}
		}
		if (type == 4) {
			k = lrand(1e8, 1e9);
			for (int i = 1; i <= n; ++i) {
				arr.push_back(k - 1);
			}
		}
        
		cout << n << sp << k << endl;
		for (auto i : arr) {
			cout << i << sp;
		}
		
		EndFor2:
		cout.close();
	}	
	
	
}
void getrev(char* src, char *dst, int len) {
	for (int i = 1; i <= len; i++) {
		dst[i] = src[len - i + 1];
	}
}
int Qcnt;


const int 
	NXT = 1, 
	DST = 0
;



void run(){
	int I;
    timeval a, b;
	double delta_t;
	int sysret;
	for(I=beg;I<end;I++){
		cmd= "./" + stdName + " > "+dataName+to_string(I)+".out < "+dataName+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		gettimeofday(&a, NULL);
		sysret = system(cmd.c_str());
		gettimeofday(&b, NULL);
		delta_t = (1e6 * (b.tv_sec - a.tv_sec) + b.tv_usec - a.tv_usec) / 1000.0;
		if (time_count) {
		    cerr<<stdName + " uses "<<delta_t<<"ms"<<endl;
		}
		
		if (check_brute) {
    		cmd= "./" + bruteName + " > brute"+to_string(I)+".out < "+dataName+to_string(I)+".in";
    		cerr<<"Run: "<<cmd<<endl;
			gettimeofday(&a, NULL);
			sysret = system(cmd.c_str());
			gettimeofday(&b, NULL);
			delta_t = (1e6 * (b.tv_sec - a.tv_sec) + b.tv_usec - a.tv_usec) / 1000.0;
    		if (brute_time_count) {
    		    cerr<<bruteName + " uses "<<delta_t<<"ms"<<endl;
    		}    		
    		cmd="diff brute"+to_string(I)+".out "+dataName+to_string(I)+".out -w";
    		if(sysret = system(cmd.c_str()) && check_out_pause){
    			getchar();
    		}
	    }
	}
	
	for(I=exbeg;I<exend;I++){
		cmd= "./" + stdName + " > "+dataName+"_ex"+to_string(I)+".out < "+dataName+"_ex"+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		gettimeofday(&a, NULL);
		sysret = system(cmd.c_str());
		gettimeofday(&b, NULL);
		delta_t = (1e6 * (b.tv_sec - a.tv_sec) + b.tv_usec - a.tv_usec) / 1000.0;
		if (time_count) {
		    cerr<<stdName + " uses "<< delta_t <<"ms"<<endl;
		}
		
		if (check_brute) {	
    		cmd= "./" + bruteName + " > brute_ex"+to_string(I)+".out < "+dataName+"_ex"+to_string(I)+".in";
    		cerr<<"Run: "<<cmd<<endl;
			gettimeofday(&a, NULL);
			sysret = system(cmd.c_str());
			gettimeofday(&b, NULL);
			delta_t = (1e6 * (b.tv_sec - a.tv_sec) + b.tv_usec - a.tv_usec) / 1000.0;
    		if (brute_time_count) {
    		    cerr<<bruteName + " uses "<< delta_t <<"ms"<<endl;
    		}    
    		cmd="diff brute_ex"+to_string(I)+".out "+dataName+"_ex"+to_string(I)+".out -w";
    		if(sysret = system(cmd.c_str()) && check_out_pause){
    			getchar();
    		}
		}
	}
	
}


_Main(){
    int loopCnt = 0;
	getprime();
	if (srand_seed == 0) {
		srand_seed = time(0);
	}
	cerr<<"seed = "<<srand_seed << endl;
	srand(srand_seed);
	if (!loop_check){
    	if (make_data) {
    	    make();
    	}
        if (run_ans) {
            run();	
        }
	} else {
	    while (1) {
	        loopCnt++;
	        if (loop_count) {
	           cerr<<"loop "<<loopCnt<<":"<<endl; 
	        }
	        if (make_data) {
	            make();
	        }
	        if (run_ans) {
	            run();
	            cerr<<endl;
	        }
	    }
	}
	


}	
vector <int> id[500050];
int mksq(int root, int l, int r, ostream &cout) {
	if (r - l + 1 < 200000 * 2 + 10) {
		mchain(root, l, r, cout);
		return r;
	}
	int mid = l + r >> 1;
	int ls = l + 200000 - 1, rs = mid + 200000 - 1;
	mchain(root, l, ls, cout);
	mchain(root, mid, rs, cout);
	int ret = mksq(ls, ls + 1, mid - 1, cout);
	mksq(rs, rs + 1, r, cout);
	return ret;
}
void mtree(int beg, int now, int end, ostream &cout) {
	for(int i = now; i <= end; i++) {
		add(i, lrand(beg, i - 1), cout);
	}
}
void mchain(int tail, int now, int end, ostream &cout) {
	for(int i = now; i <= end; i++) {
		add(i, tail, cout);
		tail = i;
	}
}
void mflower(int core, int now, int end, ostream &cout) {
	for (int i = now; i <= end; i++) {
		add(i, core, cout);
	}
}
void mbtree(int root, int now, int end, ostream &cout) {
	if (now < end) {
		int mid = now + end >> 1;
		add(root, now, cout);
		add(root, mid + 1, cout);
		mbtree(now, now + 1, mid, cout);
		mbtree(mid + 1, mid + 2, end, cout);
	} else if (now == end) {
		add(root, now, cout);
	}
}
void mworm(int root, int now, int end, ostream &cout) {
	while (now <= end) {
		add(root, now++, cout);
		if (now <= end) {
			add(root, now++, cout);
			root = now - 1;
		}
	}
}
void rand_edge(int l, int r, ostream &cout) {
	for (int i = l; i <= r; i++) {
		add(i, lrand(1, i - 1), cout);
	}
}
void add(int a, int b, ostream &cout) { //ÒªÇó±àºÅ½Ï´óµÄµãÊÇµÚÒ»´ÎÁ¬±ß 
//	if (a > b) swap(a, b);
//	setfa(b, getfa(a));
//	id[getfa(b)].push_back(b);
	if (rand() & 1) swap(a, b);
	cout << a << sp << b << endl;
}

int gap[500005];
int fa[500005];
int getfa(int a) {
	return fa[a] ? fa[a] = getfa(fa[a]) : a;
}
void setfa(int a, int b) {
	fa[a] = b;
}
int getpair(int a) {
	int t = getfa(a);
	return id[t][lrand(0, id[t].size() - 1)];
}
void randforest(int beg, int end, int cnt, ostream &cout) {
	memset(gap + beg, 0, (end - beg + 1) * sizeof(int));
	for (int i = beg ; i < beg + cnt - 1; i++) {
		gap[i] = 1;
	}
	shuffle(gap + beg, end - beg + 1);
	gap[end + 1] = 1; 
	int head = beg;
	for (int i = beg; i <= end + 1; i++) {
		if (gap[i]) {
			if (i > head) {
				mtree(head, head + 1, i - 1, cout);
			}
			head = i;
		}
	}
}	
	
	
char out_tmp[100000];
int name[100010];	
struct Edge{
	int a,b,c;
}edge[200010];	
/*
int eidx;
void add(int a, int b, int c) {
    edge[eidx++] = (Edge) {a, b, c};
}
*/
	int lim,alph;
template<typename Type>
	void shuffle(Type *beg,int size){
		int i;
		for(i=1;i<size;i++){
			swap(beg[lrand()%(i+1)],beg[i]);
		}
	}
int prime[2000000];
int primecnt;bool vis[10000005];
void getprime(){
	int i,j;
	for(i=2;i<=10000000;i++){
		if(!vis[i]){
			prime[primecnt++]=i;
		}
		for(j=0;j<primecnt && i*prime[j] <=10000000;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
	
}
	
int lrand(){
	return rand();
}
long long llrand(){
	return (long long)((long long)lrand()<<32)|((long long )lrand()<<1)^rand();
}
string outfile,cmd,infile;
template <typename Type>
string to_string(Type a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}
int randsym(){
	return (rand()&1)?-1:1;
}

void shuffleedge(Edge *beg,int n,int m,bool directed = false){
	int i;
	for(i=1;i<=n;i++){
		name[i]=i;
	}
	shuffle(name+1,n);
	shuffle(beg,m);
    if (!directed) {
    	for(i=0;i<m;i++){
    		if(rand()&1)swap(beg[i].a,beg[i].b);
    		beg[i].a=name[beg[i].a];
    		beg[i].b=name[beg[i].b];
    	}
    }
}
void inline add (int a,int b,int c,int &idx){
	edge[idx].a=a;
	edge[idx].b=b;
	edge[idx].c=c;
	idx++;
}
int arr1[400010],arr2[400010];
char type[4000010];
int mod=1e5+1;


lld lrand(lld min, lld max) {
    return llrand(min, max);
}
lld llrand(lld min, lld max) {
    return llrand() % (max - min + 1) + min;
}	
lld bit_rand() {
    return llrand() & ((1llu << lrand(0, 63)) - 1);
} 
lld bit_rand(lld min, lld max) {
    return bit_rand() % (max - min + 1) + min;
}
	
string charset = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM~!@#$%^&*()_+\"`-={}|[]\\:;¡¯<>?,./ ";	

char randchar(int l, int r) {
    return charset[lrand(l, r)];
}
char randchar() {
    return randchar(0, 32 + 26 * 2 + 10 - 1);
}
int judge_type(char a) {
    if (isdigit(a)) {
        return DIGIT;
    }
    if (islower(a)){
        return LOWER;
    }
    if (isupper(a)){
        return UPPER;
    }    
    return SYMBOL;
}
char randchar(int type) {
    char t;
    do {
        t = randchar();
    } while((judge_type(t) & type) == 0);
    return t;
}

void randRange(int beg, int end, int &l_, int &r_) {
    l_ = lrand() % (end - beg + 1);
    r_ = lrand() % (end - beg + 1 - l_);
    l_ += beg;
    r_ += l_;
}

void bit_randRange(int beg, int end, int &l_, int &r_) {
    l_ = bit_rand() % (end - beg + 1);
    r_ = bit_rand() % (end - beg + 1 - l_);
    l_ += beg;
    r_ += l_;
}
const int 
    LOWER = 1,
    UPPER = 2,
    ALPHA = 3,
    DIGIT = 4,
    SYMBOL = 8,
    ALL = 15
;
const string sp = " ";
}Maker;

/*
//#include<bits/stdc++.h>
*/

int main(){}
