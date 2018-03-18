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
string dataName = "callofdeal";
string stdName = "callofdeal";
string bruteName = "brute";
bool make_data = 1;
bool run_ans = true;

lld srand_seed = 0;

int beg = 0
,   end = 10
,   exbeg = 0
,   exend = 5
;

bool check_brute = 0;
bool check_out_pause = true;
bool loop_check = 0;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

Splay<400005>leaf, id, void_id;
void outrand(ostream &cout, int mn, int mx) {
	cout << lrand(mn, mx) << sp << lrand(mn, mx) << sp << lrand(mn, mx) << sp;
}
void make(){
	int I;
	int i,j,k;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int n;
		int mn, mx;
		
		if (I < 2) {
			n = 8;
			mn = 0; mx = 10;
		} else if (I < 4) {
			n = 100;
			mn = 0; mx = 10000;
		} else if (I < 6) {
			n = 100000;
			mn = 0; mx = 1e5;
		} else if (I < 10) {
			n = 100000;
			mn = 0; mx = 1e9;
		}
		cout << n << sp;
		outrand(cout, mn, mx);
		cout << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 2; j++) {
				outrand(cout, mn, mx);
			}
			cout << endl;
		}
		EndFor1:
		cout.close();
	}
	

	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
		int n, mn, mx;
		if (I == 0) {
			n = 100000;
			cout << n << " 0 0 0"<< endl;
			mn = 1; mx = 1e9;
			for (int i = 1; i <= n; i++) {
				for (int j = 0; j < 2; j++) {
					outrand(cout, mn, mx);
				}
				cout << endl;
			}			
		} else if (I == 1) {
			n = 100000;
			cout << n << " 1 1 1"<< endl;
			cout << "1 1 1 1 1 1" << endl;
			mn = 2; mx = 1e9;
			for (int i = 2; i <= n; i++) {
				for (int j = 0; j < 2; j++) {
					outrand(cout, mn, mx);
				}
				cout << endl;
			}						
		} else if (I == 2) {
			n = 1e5;
			cout << n << " 10 10 10" << endl;
			for (int i = 1; i <= 10000; i++) {
				mn = (i - 1) * 10 + 1; mx = (i - 1) * 10 + 9;
				for (int j = 1; j <= 9; j++) {
					outrand(cout, mn, mx);
					outrand(cout, mn, mx);
					cout << endl;
				}
				
				mn = ++mx;
				outrand(cout, mn, mx);
				outrand(cout, mn + 10, mx + 10);
				cout << endl;
			}
		} else if (I == 3) {
			n = 1e5;
			cout << n << " 1000 1000 1000" << endl;
			for (int i = 1; i <= 100; i++) {
				mn = (i - 1) * 1000 + 1; mx = (i - 1) * 1000 + 999;
				for (int j = 1; j <= 999; j++) {
					outrand(cout, mn, mx);
					outrand(cout, mn, mx);
					cout << endl;
				}
				mn = ++mx;
				outrand(cout, mn, mx);
				outrand(cout, mn + 1000, mx + 1000);
				cout << endl;
			}
		} else if (I == 4) {
			n = 1e5;
			cout << n << " 0 0 0" << endl;
			for (int i = 1; i <= n; i++) {
				outrand(cout, i - 1, i - 1);
				outrand(cout, i + 1, i + 1);
				cout << endl;
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
