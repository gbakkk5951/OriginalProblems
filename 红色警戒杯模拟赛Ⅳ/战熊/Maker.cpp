using namespace std;
#include<bits/stdc++.h>

struct _Main{
//////////////
string dataName = "warbear";
string stdName = "std";
string bruteName = "brute";

bool make_data = false;
bool run_ans = true;

int beg = 0
,   end = 5
,   exbeg = 0
,   exend = 0
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
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
        N = 100000;
        M = 100000;
        output<<N<<" "<<M<<endl;
        
        if (I <= 1 ) {
            for (i = 1; i <= N; i++) {
                output<<lrand(-1e9, 1e9)<<" ";
            }
            output<<endl;
            for (i = 1; i <= M; i++) {
                if (rand() & 1) {
                    output<<lrand(1, N)<<endl;
                } else {
                    output<<lrand(-1e9, -1)<<endl;
                }
            }            
        }
        if (I ==2) {
            for (i = 1; i <= N; i++) {
                output<<lrand(1, 10)<<" ";
            }
            output<<endl;
            for (i = 1; i <= M; i++) {
                if (rand() & 1) {
                    output<<lrand(1, N)<<endl;
                } else {
                    output<<lrand(-1e9, -1)<<endl;
                }
            }                        
        }
        if (I == 3) {
            for (i = 1; i <= N; i++) {
                if (i & 1) {
                    output<<lrand(1000000, 1000001)<<" ";
                } else {
                    output<<lrand(-10000000, 100000)<<" ";
                }
            }
            output<<endl;
            for (i = 1; i <= M; i++) {
                if (i & 1) {
                    output<<i<<endl;
                } else {
                    output<<lrand(-1e9, -1)<<endl;
                }
            }                             
            
            
        }
        if (I == 4) {
            for (i = 1; i <= N; i++) {
                if (i & 1) {
                    output<<1000000<<" ";
                } else {
                    output<<0<<" ";
                }
            }
            output<<endl;
            for (i = 1; i <= M; i++) {
                if (!(i&1) && rand() % 5 == 0) {
                    output<<lrand(-1e9,-1)<<endl;
                } else {
                    output<<i<<endl;
                }
                
            }                     
        }

		EndFor1:
		output.close();
	}
	
	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		memset(type,0,sizeof(type));
		
		EndFor2:
		output.close();
	}	
	
	
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
	
	
int name[100010];	
struct Edge{
	int a,b,c;
}edge[200010];	
	
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
void shuffleedge(Edge *beg,int n,int m){
	int i;
	for(i=1;i<=n;i++){
		name[i]=i;
	}
	shuffle(name+1,n);
	shuffle(beg,m);
	for(i=0;i<m;i++){
		if(rand()&1)swap(beg[i].a,beg[i].b);
		beg[i].a=name[beg[i].a];
		beg[i].b=name[beg[i].b];
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
