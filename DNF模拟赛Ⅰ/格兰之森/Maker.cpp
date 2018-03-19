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
#include "splay.hpp"
typedef long long lld;
struct _Main{
//////////////
string dataName = "data";
string stdName = "forest";
string bruteName = "brute_静态开块";
bool make_data = 1;
bool run_ans = true;

lld srand_seed = 0;

int beg = 10
,   end = 12
,   exbeg = 3
,   exend = 3
;

bool check_brute = 1;
bool check_out_pause = true;
bool loop_check = 0;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

//Splay<400005>leaf, id, void_id;
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
void add(int a, int b, ostream &cout) { //要求编号较大的点是第一次连边 
	if (a > b) swap(a, b);
	setfa(b, getfa(a));
	id[getfa(b)].push_back(b);
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
	memset(gap, 0, (end - beg + 1) * sizeof(int));
	for (int i = beg ; i < beg + cnt - 1; i++) {
		gap[i] = 1;
	}
	shuffle(gap, end - beg + 1);
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
void make(){
	int I;
	int i,j,k;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int IA, IB;
		int n = 500000, Qn = 10000, mn = -10000, mx = 10000;
		int mmn = mn * Qn, mmx = mx * Qn;
		int e = n - 1;
		for (int i = 1; i <= n; i++) {
			id[i].clear(); id[i].push_back(i);
			fa[i] = 0;
		}

		if (I < 2) { //随机树 
			e = n - 1;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << sp;
			}
			cout << endl;
			mtree(1, 2, n, cout);
		} else if (I < 4) {//菊花二叉树 
			e = n - 1;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << sp;
			}
			cout << endl;
			mbtree(1, 2, n >> 1, cout);
			mflower(1, (n >> 1) + 1, n, cout);
		} else if (I < 6) {//菊花链 
			e = n - 1;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << sp;
			}
			cout << endl;			
			mchain(1, 2, n >> 1, cout);
			mflower(1, (n >> 1) + 1, n, cout);
		} else if (I < 8) {//10w菊花，10w链，10万随机树，10万二叉树，10万随机边 
			e = n - 4;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << sp;
			}
			cout << endl;			
			mflower(1, 2, 1e5, cout);
			mchain(1e5 + 1, 1e5 + 2, 2e5, cout);
			mtree(2e5 + 1, 2e5 + 2, 3e5, cout);
			mbtree(3e5 + 1, 3e5 + 2, 4e5, cout);
			mtree(1, 4e5 + 1, 5e5, cout);
		} else if (I < 10) {// 1K 随机森林
			e = n - 1000;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << sp;
			}
			cout << endl;	
			randforest(1, n, 1e3, cout);
		} else if (I < 12) {//卡静态分块
			e = n - 1;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << sp;
			}
			cout << endl;	
			int mid = 1 + n >> 1;
			int ls = 2 + 700 - 1, rs = mid + 700 - 1;
			mchain(1, 2, ls, cout);
			mchain(1, mid, rs, cout);
			IA = mksq(ls, ls + 1, mid - 1, cout);
			IB = mksq(rs, rs + 1, n, cout);
		}
		if (I & 1) {
			mn = mmn = 0;
		}
		for (int Q = 1; Q <= Qn; Q++) {
			int op = lrand(1, 4);
			if (!(I & 1) && rand()%10 < 9 ) {
				op = 2;
			}		
			if ((I & 1) && op == 2) op = 1;
			int a = lrand(1, n);
			int b = getpair(a);

			if (I >= 10 && rand() % 10 < 9) {
				a = IA - 1, b = IB - 1;
			}
			if (op <= 2) {
				cout << op << sp << a << sp << b << sp << lrand(mn, mx) << endl;
			} else {
				cout << op << sp << a << sp << b << sp << lrand(mmn, mmx) << endl;
			}
		}
		EndFor1:
		cout.close();
	}
	

	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int n = 500000, e, Qn = 10000, mn = -10000, mx = 10000;
		int mmn = mn * Qn, mmx = mx * Qn;
		int a;
		for (int i = 1; i <= n; i++) {
			id[i].clear(); id[i].push_back(i);
			fa[i] = 0;
		}	
		if (I < 2) {
			e = n - 1;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << endl;
			}
			mchain(1, 2, n >> 1, cout);
			mchain(1, (n >> 1) + 1, n, cout);
			for (int Q = 1; Q <= Qn; Q++) {
	 			int op = lrand(1, 4);
				if (I % 2 == 0 && op == 2) {
					op = 1;
				}
				cout << op << sp << (n >> 1) - 1 << sp << n - 1 << sp << (op <= 2 ? lrand(mn, mx) : bit_rand(mmn, mmx)) << endl;
			}
		} else if (I == 2) {
			e = 0;
			cout << n << sp << e << sp << Qn << endl;
			for (int i = 1; i <= n; i++) {
				cout << lrand(mn, mx) << endl;
			}
			for (int Q = 1; Q <= Qn; Q++) {
	 			int op = lrand(1, 4);
				int t = lrand(1, n);
				cout << op << sp << t << sp << t << sp << (op <= 2 ? lrand(mn, mx) : bit_rand(mmn, mmx)) << endl;
			}
		}
        
		EndFor2:
		cout.close();
	}	
	
	
}
int Qcnt;


const int 
	NXT = 1, 
	DST = 0
;



void run(){
	int I;
    float a, b;
	for(I=beg;I<end;I++){
		cmd= stdName + ".exe > "+dataName+to_string(I)+".out < "+dataName+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		a = clock();
		system(cmd.c_str());
		b = clock();
		if (time_count) {
		    cerr<<stdName + " uses "<<b - a<<"ms"<<endl;
		}
		
		if (check_brute) {
    		cmd= bruteName + ".exe > brute"+to_string(I)+".out < "+dataName+to_string(I)+".in";
    		cerr<<"Run: "<<cmd<<endl;
            a = clock();
            system(cmd.c_str());
    		b = clock();
    		if (brute_time_count) {
    		    cerr<<bruteName + " uses "<<b - a<<"ms"<<endl;
    		}    		
    		cmd="fc brute"+to_string(I)+".out "+dataName+to_string(I)+".out";
    		if(system(cmd.c_str()) && check_out_pause){
    			system("pause");
    		}
	    }
	}
	
	for(I=exbeg;I<exend;I++){
		cmd= stdName + ".exe > "+dataName+"_ex"+to_string(I)+".out < "+dataName+"_ex"+to_string(I)+".in";
		cerr<<"Run: "<<cmd<<endl;
		a = clock();
		system(cmd.c_str());
		b = clock();
		if (time_count) {
		    cerr<<stdName + " uses "<<b - a<<"ms"<<endl<<endl;
		}
		
		if (check_brute) {	
    		cmd= bruteName + ".exe > brute_ex"+to_string(I)+".out < "+dataName+"_ex"+to_string(I)+".in";
    		cerr<<"Run: "<<cmd<<endl;
            a = clock();
            system(cmd.c_str());
    		b = clock();
    		if (brute_time_count) {
    		    cerr<<bruteName + " uses "<<b - a<<"ms"<<endl;
    		}    
    		cmd="fc brute_ex"+to_string(I)+".out "+dataName+"_ex"+to_string(I)+".out";
    		if(system(cmd.c_str()) && check_out_pause){
    			system("pause");
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
	return (rand()<<16) | (rand()<<1) ^rand();	
}
long long llrand(){
	return (long long)((long long)lrand()<<32)|((long long )lrand()<<1)^rand();
}
string outfile,cmd,infile;
string to_string(int a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}
int randsym(){
	return (rand()&1)?-1:1;
}

string arr[100010];
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
    return llrand() & ((1u << lrand(0, 63)) - 1);
} 
lld bit_rand(lld min, lld max) {
    return bit_rand() % (max - min + 1) + min;
}
	
string charset = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM~!@#$%^&*()_+\"`-={}|[]\\:;’<>?,./ ";	

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
