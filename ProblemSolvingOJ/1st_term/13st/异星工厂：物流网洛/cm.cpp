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
#include <cassert>
//#include "splay.hpp"
typedef long long lld;
const int MXN = 52;
struct _Main{
//////////////
string dataName = "tester";
string stdName = "std";
string bruteName = "brute";
bool make_data = 1;
bool run_ans = 1;

lld srand_seed = 0;

int beg = 0
,   end = 1
,   exbeg = 0
,   exend = 0
;

bool check_brute = 1;
bool check_out_pause = true;
bool loop_check = 1;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

//Splay<400005>leaf, id, void_id;
int d[MXN][MXN];
void dswap(int a, int b, int n) {
	for (int i = 1; i <= n; ++i) {
		swap(d[i][a], d[i][b]);
	}
	for (int i = 1; i <= n; ++i) {
		swap(d[a][i], d[b][i]);
	}
}
void init(int n) {
	clear();
	for (int i = 1; i <= n; ++i) {
		d[1][i] = d[i][n] = d[i][i] = 1;
	}
}
void clear() {
	memset(d, 0, sizeof(d));
}
void transitive(int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (d[i][j]) for (int k = 1; k <= n; ++k) {
				d[i][k] |= d[j][k];
			}
		}
	}
}
int notleaves[MXN];
void clearleaves() {
	memset(notleaves, 0, sizeof(notleaves));
}
void maketree(int end, int begin = 2) {//root is 1
	for (int i = begin; i <= end; ++i) {
		int to = lrand(1, i - 1);
		notleaves[to] = 1;
		d[to][i] = 1;
	}
}
void makeanothertree(int begin, int n) {//root is n
//	cerr << "mat " << begin << sp << n << endl;
	fflush(stderr);
	for (int i = begin; i < n; ++i) {
		int to = lrand(i + 1, n);
		notleaves[to] = 1;
		d[i][to] = 1;
	}
}
void dshuffle(int n) {
	for (int i = 2; i <= n; ++i) {
		dswap(i, lrand(1, i), n);
	}
}
void linktree(int smallerend, int n) {
//	cerr << "linktree" << endl;
	fflush(stderr);
	int sn = 0, bn = 0;
	int smaller[51], bigger[51];
	for (int i = 1; i <= n; i++) {
		if (!notleaves[i]) {
			if (i <= smallerend)
				smaller[sn++] = i;
			else bigger[bn++] = i;
		}
	}
//	cerr << "sn = " << sn << "bn = " << bn << endl;
	fflush(stderr);
	shuffle(smaller, sn);
	shuffle(bigger, bn);
	for (int i = 0; i < bn && i < sn; ++i) {
		d[smaller[i]][bigger[i]] = 1;
	}
	if (lrand(0, 3)) for (int i = min(bn, sn); i < max(bn, sn); ++i) {
		d[smaller[min(i, sn - 1)]][bigger[min(i, bn - 1)]] = 1;
	}
}
void print(int n, ostream & cout, int noise = 0, int shuffle = 1) {
	if (shuffle) {
		dshuffle(n);
	}
	if (lrand(0, 5)) noise = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << (d[i][j] ^ (noise && (lrand(0, 31) == 0))) << sp;
		}
		cout << endl;
	}
}
void make(){
	int I;
	int i,j,k;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int rem = 5e4;	
		vector<int> lens;
		int extra_begin;
		if (I == 0) {
			
			lens.push_back(lrand(4, 7));
//			lens.push_back(lrand(4, 11));
//			lens.push_back(lrand(4, 11));
//			lens.push_back(lrand(4, 11));
//			lens.push_back(lrand(4, 5));
//			lens.push_back(lrand(4, 5));
//			lens.push_back(lrand(4, 5));
		
		} else
		if (I < 5) { // (5, to 10)
			while (rem >= 10) {
				int l = lrand(3, 4);
				rem -= l;
				lens.push_back(l);
			}
		} else if (I == 5) {
			for (int L = 1; L < 7; ++L) {
				int tot = ((1 << ((L - 1) * (L - 1) - (L - 2)))) + min(2LL << (L * L), 50LL) + min(2LL << (L * L), 50LL);
				if (rem < tot * L) {
					break;
				}
				rem -= tot * L;
				while (tot--) {
					lens.push_back(L);
				}
			}
			
			extra_begin = lens.size();
			
			while (rem > 1) {
				break;
				int t = lrand(2, min(5, rem));
				lens.push_back(t);
				rem -= t;
			}
		} else
		if (I < 20) {
			while (rem > 100) {
				int l;
				if (I >= 15) {
					l = lrand(43, 50);
				} else
				if (I >= 10) {
					l = lrand(30, 42);
				} else {
					l = lrand(11, 29);
				}
				rem -= l;
				lens.push_back(l);
			}
			while (rem > 1) {
				int t = lrand(2, min(5, rem));
				lens.push_back(t);
				rem -= t;
			}
		}
		
		
		int L = 1, cnt = 1, mjl, rndl, rndgoodl, totlen;
		int S = 0; 
		cout << lens.size() << endl;
		for (int i = 0; i < lens.size(); ++i) {
			cout << lens[i] << endl;
			if (I == 5 && i < extra_begin) {
//				cerr << "short" << endl;
				fflush(stderr);
				assert(L == lens[i]);
				mjl = ((1 << ((L - 1) * (L - 1) - (L - 2)))), rndl = min(2LL << (L * L), 50LL), rndgoodl = min(2LL << (L * L), 50LL);
				totlen = mjl + rndl + rndgoodl;
				if ( cnt > mjl + rndl) {
					for (int i = 1; i <= L; ++i) {
						for (int j = i + 1; j <= L; ++j) {
							d[i][j] = lrand(0, 3) == 0;
						}
					}
					transitive(L);
				} else
				if (cnt > mjl) {
					int tmp = lrand(0, 1);
					for (int i = 1; i <= L; ++i) {
						for (int j = (tmp ? i : 1); j <= L; ++j) {
							d[i][j] = lrand(0, 1) == 0;
						}
					}
				} else {
					init(L);
					int x, y;
					if (L > 1) for (int i = 0; i < (L - 1) * (L - 1) - (L - 2); ++i) {
						if (L > 2)x = 2 + (i / (L - 2));
						else x = 2;
						y = 1 + i - (x - 2) * (L - 2);
						y += y >= x;
						d[x][y] = (S >> i) & 1;
//						cout << "x = " << x << " y = " << y << " i = " << i << endl;
					}
				}
				++cnt;
				S++;
				if (cnt > totlen) {
					++L;
					S = 0;
					cnt = 1;
				}
			} else {
				L = lens[i];
				if (lrand(0, 13)) {
					if (lrand(0, 17))init(L);
					else clear();
					if (lrand(0, 1)) {
						int tmp = lrand(0, 3);
						for (int i = 1; i <= L; ++i) {
							for (int j = (tmp ? i : 1); j <= L; ++j) {
								d[i][j] |= lrand(0, 1) == 0;
							}
						}
					} else {
						
//						cerr << "B" << endl;
//						cerr << L << endl;
//						fflush(stderr);
						int mid = lrand(1, L - 1);
						clearleaves();
						maketree(mid);
						makeanothertree(mid + 1, L);
//						cout << "tree" << endl;
						if (lrand(0, 4)) linktree(mid, L);
					}
					if (lrand(0, 7)) {
//						cerr << "C" << endl;
						fflush(stderr);
						transitive(L);
					}
				} else if (lrand(0, 17)){
///t/						cerr << "d" << endl;
						fflush(stderr);
					for (int i = 1; i <= L; ++i) {
						for (int j = 1; j <= L; ++j) {
							d[i][j] = lrand(0, 1);
						}
					}
				} else {
//						cerr << "E" << endl;
						fflush(stderr);
					clear();
				}
			}
			print(lens[i], cout, I != 5 || i >= extra_begin, I != 5 || lrand(0, 1));
		}
		
		
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
    		cmd="diff brute"+to_string(I)+".out "+dataName+to_string(I)+".out";
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
    		cmd="diff brute_ex"+to_string(I)+".out "+dataName+"_ex"+to_string(I)+".out";
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
