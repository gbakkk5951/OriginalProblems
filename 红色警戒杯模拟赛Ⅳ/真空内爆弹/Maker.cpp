using namespace std;
#include<bits/stdc++.h>
typedef long long lld;
struct _Main{
//////////////
string dataName = "imploder";
string stdName = "std";
string bruteName = "brute";

bool make_data = true;
bool run_ans = true;

int beg = 0
,   end = 6
,   exbeg = 0
,   exend = 2
;

bool check_brute = false;
bool check_out_pause = true;
bool loop_check = false;
bool loop_count = true;
bool time_count = true;
bool brute_time_count = true;

//////////////

void make(){
	int I;
	int i,j,k;
	int A,B,C;
	int N,M,Q,K;
	int t;
	lld mod;
	lld mx_val;
	int base;
	int bloc;
	int a, b;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
        N = 10000 * (I + 1); M = 10000 * (I + 1);
        if (I == 5) {
            N = 10;
            M = 30;
        }
        output << N <<" "<< M << endl;
        for (i = 1; i <= N; i++) {
            output<< lrand(-10000, 10000) << " " << lrand(-10000, 10000) << endl;
        }
        for (i = 1; i <= M; i++) {
            int oper = rand() % 8;
            output << oper;
            if (oper != 7) {
                int l, r;
                if (I < 5000) {
                    l = 1 + bit_rand(0, 450);
                    r = N - bit_rand(0, 450);
                }
                randRange(1, N, l, r);
                output <<" " << l <<" " << r;
                if (oper == 0 || oper == 1) {
                    output << " " << lrand(-100, 100);
                } 
                if (oper == 6) {
                    output << " " << lrand(0, 360);
                }
            } else {
                output << " "  << lrand(1, N);
            }
            output << endl;
        }
        
		EndFor1:
		output.close();
	}
	
	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
        
        N = 50000; M = 50000;
        output << N <<" "<< M << endl;
        if (I == 0) {
            for (i = 1; i <= N; i++) {
                output<< lrand(0, 10000) << " " << lrand(0, 10000) << endl;
            }
            for (i = 1; i <= M; i++) {
                int l, r;
                int oper = rand() % 2;
                output << oper;
                l = 1 + bit_rand(0, 4500);
                r = N - bit_rand(0, 4500);
                randRange(1, N, l, r);
                output <<" " << l <<" " << r;
                if (oper == 0 || oper == 1) {
                    output << " " << lrand(1, 100);
                }
                output << endl;
            }
        }
        if (I == 1) {
            for (i = 1; i <= N; i++) {
                output<< lrand(-10000, 10000) << " " << lrand(-10000, 10000) << endl;
            }
            for (i = 1; i <= M; i++) {
                int oper = 6;
                output << oper;
                if (oper != 7) {
                    int l, r;
                    if (I < 5000) {
                        l = 1 + bit_rand(0, 450);
                        r = N - bit_rand(0, 450);
                    }
                    randRange(1, N, l, r);
                    output <<" " << l <<" " << r;
                    if (oper == 0 || oper == 1) {
                        output << " " << lrand(-100, 100);
                    } 
                    if (oper == 6) {
                        output << " " << lrand(0, 360);
                    }
                } else {
                    output << " " << lrand(1, N);
                }
                output << endl;
            }
                
        }
		
		EndFor2:
		output.close();
	}	
	
	
}
int id[12][105];

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
	srand(time(0));
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

int eidx;
void add(int a, int b, int c) {
    edge[eidx++] = (Edge) {a, b, c};
}

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

int lrand(int min, int max) {
    return llrand() % ((long long)max - min + 1) + min;
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
void randRange(int beg, int end, int &l_, int &r_) {
    l_ = lrand() % (end - beg + 1);
    r_ = lrand() % (end - beg + 1 - l_);
    l_ += beg;
    r_ += l_;
}


}Maker;

/*
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<fstream>
*/

int main(){}
