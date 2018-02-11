<<<<<<< HEAD
<<<<<<< HEAD
 using namespace std;
=======
<<<<<<< HEAD
=======
>>>>>>> 92143feda58d333f56964ba6bd00b96a52cdfa69
using namespace std;
=======
 using namespace std;
>>>>>>> cbc867c48460d8e655aec99718509fe543452d4c
<<<<<<< HEAD
>>>>>>> 92143feda58d333f56964ba6bd00b96a52cdfa69
=======
>>>>>>> 92143feda58d333f56964ba6bd00b96a52cdfa69
#include<bits/stdc++.h>
typedef long long lld;
struct _Main{
//////////////
string dataName = "vx";
string stdName = "std";
string bruteName = "brute";

bool make_data = true;
bool run_ans = true;

int beg = 0
,   end = 5
,   exbeg = 0
,   exend = 1
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
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
        int len = 1e5, Q = 500;
        cout <<len <<" " << Q << endl;
        if (I == 0) { 
            for (i = 1; i <= len; i++) {
                cout << randchar();
            }
        } 
        if (I == 1) {
            for (i = 1; i <= len; i++) {
                cout << randchar(1, 50);
            }            
        }
        if (I == 2) {
            for (i = 1; i <= len; i++) {
                cout << randchar(1, 10);
            }            
        }        
        if (I == 3) {
            for (i = 1; i <= len; i++) {
                cout << randchar(1, 3);
            }            
        }     
        if (I == 4) {
            for (i = 1; i <= len; i++) {
                cout << randchar(1, 2);
            }            
        }           
        cout << endl;
        for (i = 1; i <= Q; i++) {
            if (i == 1) {
                cout << 0;
            } else if (i == 2) {
                cout << (int)1e9 + 7;  
            } else {
                cout << bit_rand(1, 1e18);
            }
            cout<<endl;
        }
        
		EndFor1:
		cout.close();
	}
	
	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream cout(outfile.c_str());
        int len = 1e5, Q = 500;
        cout <<len <<" " << Q << endl;        
        if (I == 0) {
            for (i = 1; i <= len; i++) {
                cout <<'a';
            }
        }
        
        cout << endl;
        for (i = 1; i <= Q; i++) {
            if (i == 1) {
                cout << 0;
            } else if (i == 2) {
                cout << (int)1e9 + 7;  
            } else if (i == 3) {
                cout << 285700001 << endl;
            
            } else if (i == 4) {
                cout << (int)1e9 + 7 - 1 << endl;
            } else {
                cout << lrand(1, 1e18);
            }
            cout<<endl;
        }		
		EndFor2:
		cout.close();
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

<<<<<<< HEAD
<<<<<<< HEAD
lld lrand(lld min, lld max) {
=======
<<<<<<< HEAD
=======
>>>>>>> 92143feda58d333f56964ba6bd00b96a52cdfa69
int lrand(int min, int max) {
=======
lld lrand(lld min, lld max) {
>>>>>>> cbc867c48460d8e655aec99718509fe543452d4c
<<<<<<< HEAD
>>>>>>> 92143feda58d333f56964ba6bd00b96a52cdfa69
=======
>>>>>>> 92143feda58d333f56964ba6bd00b96a52cdfa69
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
	
string charset = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM~!@#$%^&*()_+\"`-={}|[]\\:;¡¯<>?,./ ";	

char randchar(int l = 0, int r = 32 + 26 * 2 + 10 - 1) {
    return charset[lrand(l, r)];
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
