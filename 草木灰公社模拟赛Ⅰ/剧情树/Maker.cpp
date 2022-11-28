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
#include "splay.hpp"
typedef long long lld;
struct _Main{
//////////////
string dataName = "plot";
string stdName = "plot";
string bruteName = "test";
bool make_data = 0;
bool run_ans = true;

lld srand_seed = 0;

int beg = 0
,   end = 12
,   exbeg = 0
,   exend = 10
;

bool check_brute = 1;
bool check_out_pause = true;
bool loop_check = 1;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

Splay<400005>leaf, id, void_id;
void make(){
	int I;
	int i,j,k;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		
		int m;
		int mxv, mxid = 100000;
		m = 100000;
		if (I >> 1 == 0) {
			mxv = 0;
			mxid = 1000;
		} else if(I >> 1 == 1) {
			mxv = 1;
			mxid = 50000;
		} else if (I >> 1 == 2) {
			mxv = 26;
			mxid = 10000;
		} else if (I >> 1 == 3) {
			mxv = 500;
		} else if (I >> 1 == 4) {
			mxv = 100000;
		} else if (I >> 1 == 5) {
			mxv = 100000;
		}
		int Q;
		leaf.clear();
		id.clear();
		void_id.clear();
		eidx = 0;
		memset(head, 0, sizeof(head));
		memset(out, 0, sizeof(head));
//		printf("leaf + 0\nid + 0\n");
		leaf.insert(0);
		id.insert(0);
		for (i = 1; i <= mxid; i++) {
			void_id.insert(i);
		}
		cout << m << endl;
		for (Q = 1; Q <= m; Q++) {
//			cerr<< "Q = "<< Q<< endl;
			if (Q == m) {
				cout << "2 0" << endl;
				continue;
			}
			if (rand() & 1/*I != 4 && ((I & 1) ? (rand() % 5 == 1) : (rand() % 3 == 1) )*/) {
				int t;
				if (/*(I & 1) ? (rand() % 50 == 1) : (rand() % 10 == 1)*/ rand() & 1) {
					
					t = id.getRand();
					if (t == 0) {
						Q--;
						continue;
					}
					del(t, cout);
				} else {
					t = leaf.getRand();
					if (t == 0) {
						Q--;
						continue;
					}
					del(t, cout);
				}
			} else if (rand() % 3 < 2){
				if (void_id.size() == 0) {
					Q--;
					continue;
				}
				int t;
				ins(id.getRand(), t = void_id.getRand(), bit_rand(0, mxv), cout);
				if (rand() & 1) {
					Q++;
					ask(t, cout);
				}
			} else {
				ask(leaf.getRand(), cout);
			}
		}
		
		EndFor1:
		cout.close();
	}
	

	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int m = 100000, mxid = 100000, mxv = 25000;
		leaf.clear();
		id.clear();
		void_id.clear();
		eidx = 0;
		memset(head, 0, sizeof(head));
		memset(out, 0, sizeof(head));
		leaf.insert(0);
		id.insert(0);
		Qcnt = 0;
		
		for (i = 1; i <= mxid; i++) {
			void_id.insert(i);
		}
		cout << m << endl;
        if (I == 0) { // 3W Q+菊花 + 2W Q, + 2w rand; 
        	for (i = 1; i <= 30000; i++) {
        		ins(0, i, lrand(0, mxv), cout);
        		ask(i, cout);
        	}
        	for (i = 1; i <= 20000; i++) {
        		ask(leaf.getRand(), cout);
        	}
        	for (i = 1; i <= 20000; i++) {
        		randOper(mxv, cout);
        	}
        } else if (I == 1) { // 4.5w 菊花 + 4.5w Q + 1w rand
			for (i = 1; i <= 45000; i++) {
        		ins(0, i, lrand(0, mxv), cout);
        	}
        	for (i = 1; i <= 45000; i++) {
        		ask(i, cout);
        	}        	
        	for (i = 1; i <= 10000; i++) {
        		randOper(mxv, cout);
        	}
        } else if (I == 2) { // 2 * 20000链 + Q，2W rand  
        	mxv = 1;
        	int a[2] = {0, 0};
        	int idx = 0;
        	for (i = 1; i <= 20000; i++) {
	        	for (j = 0; j < 2; j++) {
					ins(a[j], ++idx, lrand(0, mxv), cout);
	        		ask(idx, cout);
	        		a[j] = idx;
        		}
        	}
        	for (i = 1; i <= 20000; i++) {
        		randOper(min(100000, mxv + 3), cout);
        	}
        } else if (I == 3) { //3W第一排 1~ 3W， 3w第二排 0， 3WQ, 1W rand 
        	for (i = 0; i <= 29999; i++) {
        		ins(0, i + 1, i, cout);
        	} 
        	for (i = 1; i <= 30000; i++) {
        		ins(i, 30000 + i, 0, cout);
        	}
        	for (i = 1; i <= 30000; i++) {
        		ask(i + 30000, cout);
        	}
        	for (i = 1; i <= 10000; i++) {
        		randOper(2, cout);
        	}
        } else if (I == 4) {// 4 * 10000 链 （1/2概率问）+ 2W 随机插入 + 剩下随机 
			
			mxv = 2;
			int t[4] = {0,0,0,0}, idx = 1; 
			for (i = 1; i <= 10000; i++) {
				for (j = 0; j < 4; j++) {
					ins(t[j], ++idx, lrand(0, mxv), cout);
					t[j] = idx;
					if (rand() & 1) {
						ask(idx, cout);
					}
				}
			}
			for (i = 1; i <= 20000; i++) {
				ins(id.getRand(), void_id.getRand(), lrand(0, 20), cout);
			}
			for (i = Qcnt + 1; i <= m; i++) {
				randOper(mxv, cout);
			}
		} else if (I == 5) { //1W链 + 4W（插入、删除） + 1W随机 
			mxv = 2;
			for (i = 1; i <= 10000; i++) {
				ins(i - 1, i, lrand(0, mxv), cout);
			} 
			for (i = 1; i <= 40000; i++) {
				int t = lrand(10001, 100000);
				ins(10000, t, lrand(0, mxv), cout);
				del(t, cout);
			}
			for (i = 1; i <= 10000; i++) {
				randOper(5, cout);
			}
		} else if (I == 6) { //卡单倍+无回收+暴力删除  A
			mxv = 9;
			for (i = 1; i <= 4; i++) {
				int core = 0, t;
				core = 1;
				ins(0, 1, lrand(0, mxv), cout);
				for (j = 2; j <= 19999; j++) {
					if (j % 3 == 1) {
						ask(leaf.getRand(), cout);
					} else if (j % 3 == 2){
						ins(core, void_id.getRand(), lrand(0, mxv), cout);
					} else {
						t = void_id.getRand();
						ins(core, t, lrand(0, mxv), cout);
						core = t;						
					}
				}
				del(1, cout);
			}
			for (i = Qcnt + 1; i <= m; i++) {
				randOper(mxv, cout);
			}
		} else if (I == 7) {//卡单倍+无回收+暴力删除 B
			mxv = 9;
			for (i = 1; i <= 4; i++) {
				int core = 0, t;
				core = 1;
				ins(0, 1, lrand(0, mxv), cout);
				for (j = 2; j <= 19998; j++) {
					if (j % 2 == 1){
						ins(core, void_id.getRand(), lrand(0, mxv), cout);
					} else {
						t = void_id.getRand();
						ins(core, t, lrand(0, mxv), cout);
						core = t;						
					}
				}
				ask(core, cout);
				del(1, cout);
			}
			for (i = Qcnt + 1; i <= m; i++) {
				randOper(mxv, cout);
			}			
		} else if (I == 8) {//卡单base小 
			ins(0, 1, 1, cout);
			for (int i = 0; i < 49999; i++) {
				ins(0, 100000 - i, 100000 - i, cout);
				ask(100000 - i, cout);
			}
			del(0, cout);
		} else if (I == 9) {
			ins(0, 1, 1, cout);
			for (int i = 0; i < 49999; i++) {
				ins(0, 50001 - i, 50001 - i, cout);
				ask(50001 - i, cout);
			}
			del(0, cout);			
		}
        
		EndFor2:
		cout.close();
	}	
	
	
}
int Qcnt;
	void randOper(int mxv, ostream &cout) {
		FuncBeg:
		if (rand() % 5 == 1) {
			int t;
			if (rand() % 10 == 1) {
				t = id.getRand();
				if (t == 0) {
					goto FuncBeg;
				}
				del(t, cout);
			} else {
				t = leaf.getRand();
				if (t == 0) {
					goto FuncBeg;
				}
				del(t, cout);
			}
		} else if (rand() % 2 < 1){
			if (void_id.size() == 0) {
				goto FuncBeg;
			}
			int t;
			ins(id.getRand(), t = void_id.getRand(), bit_rand(0, mxv), cout);
		} else {
			ask(leaf.getRand(), cout);
		}		
	}

const int 
	NXT = 1, 
	DST = 0
;
int out[100010];
int f[100010];
int s[100010][2];
int head[100010];
int eidx;
void inline add(int f, int _s) {
	eidx++;
	s[eidx][DST] = _s;
	s[eidx][NXT] = head[f];
	head[f] = eidx;
}
void del(int nd, ostream &cout) {
	Qcnt++;
	cout << 2 << " " << nd << endl;	
	int f = this->f[nd];
	only_del(nd);
	if (out[f] == 0) {
		leaf.insert(f);
	}
} 
void only_del(int nd) {
	int scnt = 0;
	for (int i = head[nd]; i; i = s[i][NXT]) {
		int t;
		if (f[t = s[i][DST]] == nd) {
			only_del(t);
			scnt++;
		}
	}
	--out[f[nd]];
	if (scnt == 0) {
		leaf.erase(nd);
	}
	id.erase(nd);
	void_id.insert(nd);
	head[nd] = 0;
	f[nd] = -1;
}
void ins(int f, int s, int v, ostream &cout) {
	Qcnt++;
	cout << "1 "<< f<<" "<<s<<" "<< v << endl;
	add(f, s);
	this->f[s] = f;
	if (++out[f] == 1) {
		leaf.erase(f);
	}
	leaf.insert(s);
	id.insert(s);
	void_id.erase(s);
}
void ask(int nd, ostream &cout) {
	Qcnt++;
	cout <<"3 "<< nd << endl;
}


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
			swap(beg[rand()%(i+1)],beg[i]);
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
}Maker;

/*
//#include<bits/stdc++.h>
*/

int main(){}
