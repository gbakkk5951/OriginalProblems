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
,   end = 30
,   exbeg = 0
,   exend = 0
;

bool check_brute = 0;
bool check_out_pause = true;
bool loop_check = 0;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

//Splay<400005>leaf, id, void_id;

int GetPhi(int p)
{

	int Phi = p, Remain = p;
	for (int i = 2; i * i <= Remain; ++i)
	{
		if (Remain % i == 0)
		{
			Phi = (lld)Phi * (i - 1) / i; // 找个爆的
			do {
				Remain /= i;
			} while (Remain % i == 0);
		}
	}
	if (Remain > 1)
	{
		Phi = (lld)Phi * (Remain - 1) / Remain; // 找个爆的
	}
	return Phi;
}
int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}
void make(){
	int I;
	int i,j,k;
	typedef pair<int, int> p;
	vector<p> Edges;
	vector<int> Name;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		if (I == 18)
		{
			cout << "6 000000000000000000000000000000000000000000000000000000000000000000000000000000000000 1" << endl;
			cout.close();
			continue;
		}
		if (I == 19)
		{
			cout << "6 0 1" << endl;
			cout.close();
			continue;
		}
		int Len = lrand(5e5, 1e6);
		int p[] = {(int)30047 * 30047, lrand(2, (int)2.1e9), 998244353, 2 * (int)(1e9 + 9), 223092870, 1 << 30, 3 << 28, 30047 * 30091, 1};
		lld a = lrand(1, 1e9);
		int Base = 1, Mod = 1;
		int PrimeIndex = I % (sizeof(p) / sizeof(p[0]));
		int Type = I / (sizeof(p) / sizeof(p[0]));
		Mod = p[PrimeIndex];
		lld Loop = GetPhi(Mod) * (lld) Mod;
		do {
			Base = lrand(2, 2.1e9);
		} while (gcd(Base, Mod) != 1);

		cout << Base << sp;
		
		if (Type == 0)
		{
			for (int i = 0; i + 20 < Len; i += 20)
			{
				cout << Loop;
			}
		}
		else if (Type == 1)
		{
			for (int i = 0; i + 20 < Len; i += 1)
			{
				cout << 0;
			}
		}
		else
		{
			for (int i = 0; i < Len; ++i)
			{
				cout << lrand(0, 9);
			}
		}
		cout << sp << Mod;
		

		EndFor1:
		cout.close();
	}
	

	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		
        
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
