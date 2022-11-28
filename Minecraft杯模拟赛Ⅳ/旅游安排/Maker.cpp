using namespace std;
#include<bits/stdc++.h>
typedef long long lld;
struct _Main{
//////////////
string dataName = "数据";
string stdName = "std";
string bruteName = "brute_EK";

bool make_data = true;
bool run_ans = true;

int beg = 0
,   end = 20
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
	lld mod;
	lld mx_val;
	int base;
	int bloc;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
        
        eidx = 0;
        if (I >> 1 == 0) {
            base = 55;
            N = (2 * 27 + 1) * 10;
            for (i = 0; i <= 9; i++) {
                for (j = 1; j <= 27; j++) {
                    edge[eidx++] = (Edge){i * base + j, i * base + 1 + j, -( (1 << j) - 1)};
                    edge[eidx++] = (Edge){i * base + 28 + j, i * base + 1 + j, -(1 << j)};
                    edge[eidx++] = (Edge){i * base + j, i * base + 28 + j, 0};
                }
            }
        } else if (I >> 1 == 1) {
            N = 0;
            for (i = 1; i <= 10; i++) {
                for (j = 1; j <= 100; j++) {
                    id[i][j] = ++N;
                }
            }
            for (i = 1; i <= 10; i++) {
                for (j = 1; j <= 100; j++) {
                    if (j - 1 > 0) {
                        add(id[i][j], id[i][j - 1], lrand(10, 30000));
                    }
                    if (j + 1 <= 100) {
                        add(id[i][j], id[i][j + 1], lrand(10, 30000));
                    }
                    if (i - 1 > 0) {
                        add(id[i][j], id[i - 1][j], lrand(10, 30000));
                    }
                    if (i + 1 <= 100) {
                        add(id[i][j], id[i + 1][j], lrand(10, 30000));
                    }
                }
            }
        } else if (I >> 1 == 2) {
            N = 1000, M = 5000;
            for (i = 1; i <= M; i++) {
                add(lrand(1, N), lrand(1, N), bit_rand(0,1e9));
            }
        } else if (I >> 1 == 3) {
            N = 1000, M = 5000;
            for (i = 1; i <= M; i++) {
                add(lrand(1, N), lrand(1, N), lrand(0,1e9));
            }            
        } else if(I >> 1 == 4) {
            N = 1000, M = 5000;
            for (i = 1; i <= M; i++) {
                add(lrand(1, N), lrand(1, N), llrand(-1e9,1e9));
            }          
        } else if (I >> 1 == 5) {
            N = 1000, M = 5000;
            for (i = 1; i <= M; i++) {
                if (rand() %80 == 1) {
                    add(lrand(1, N), lrand(1, N), lrand(-50,0));
                } else {
                    add(lrand(1, N), lrand(1, N), bit_rand(0,1e9));
                }
            }
        } else if (I >> 1 == 6) {
            N = 1000, M = 5000;
            for (i = 1; i <= M; i++) {
                if (rand() %50 == 1) {
                    add(lrand(1, N), lrand(1, N), llrand(-5000,0));
                } else {
                    add(lrand(1, N), lrand(1, N), llrand(0,1e9));
                }
            }            
        } else if (I >> 1 == 7) {
            N = 1000;
            for (i = 1; i <= N; i++) {
                add(1, i, (N - i + 1) * 2 + 1);
                add(i, i - 1, 1);
            }
        } else if (I >> 1 == 8) {
            N = 1000;
            base = 0;
            while (base < N) {
                if (N - base < 10) {
                    bloc = N - base; 
                } else {
                    bloc = lrand(10, min(N - base, 50));
                }
                M = bloc * 5;
                for (i = 1; i <= M; i++) {
                    if (rand() % 150 == 1) {
                        add(base + lrand(1, bloc), base + lrand(1, bloc), lrand(-10, 1));
                    } else {
                        add(base + lrand(1, bloc), base + lrand(1, bloc), 
                        rand() & 1 ? bit_rand(0, 1e9) : lrand(0, 10000));
                    }
                }
                base += bloc;          
            }
        } else if (I >> 1 == 9) {
            N = 70;
            for (i = 1; i <= N; i++) {
                for (j = 1; j <= N; j++) {
                    if (i != j) {
                        add(i, j, bit_rand(0, 1e9));
                    }
                }
            }
        }
        
        
        M = eidx;
        output << N <<" " << M <<endl;
        if (I & 1) {
            shuffleedge(edge, N, M, true);
        }
        
        for (i = 0; i < M; i++) {
            output<<edge[i].a << " " << edge[i].b << " " << edge[i].c << endl;
        }
        //目的地数目 外出数量 消费次数 容纳量 消费水平 
        for (i = 1; i <= N; i++) {
            if (I & 1) {
                output << lrand(1, 10) << " " 
                       << lrand(0, 1e9) << " " 
                       << lrand(0, 30) << " " 
                       << lrand(0, 1e9) << " " 
                       << lrand(0, 30) <<endl;
            } else {
                output << 10 << " " 
                       << bit_rand(1, 1e9) << " " 
                       << lrand(1, 30) << " " 
                       << bit_rand(1, 1e9) << " " 
                       << lrand(1, 30) <<endl;
            }
        }
        
        
		EndFor1:
		output.close();
	}
	
	
	for(I=exbeg;I<exend;I++){
		outfile=dataName+"_ex"+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
        eidx = 0;
        
        N = 70;
        if (I >> 1 == 0) {
            for (i = 1; i <= N; i++) {
                for (j = 1; j <= N; j++) {
                    if (i != j) {
                        add(i, j, 1);
                    }
                }
            }
        } else if (I >> 1 == 1) {
            N = 1000;
            for (i = 1; i <= N; i++) {
                add(1, i, (N - i + 1) * 2 + 1);
                add(i, i - 1, 1);
            }    
        }

                
        
        M = eidx;
        output << N <<" " << M <<endl;
        if (I & 1) {
            shuffleedge(edge, N, M, true);
        }
        
        for (i = 0; i < M; i++) {
            output<<edge[i].a << " " << edge[i].b << " " << edge[i].c << endl;
        }
        //目的地数目 外出数量 消费次数 容纳量 消费水平 
        for (i = 1; i <= N; i++) {
            if (I & 1) {
                output << lrand(1, 10) << " " 
                       << lrand(0, 1e9) << " " 
                       << lrand(0, 30) << " " 
                       << lrand(0, 1e9) << " " 
                       << lrand(0, 30) <<endl;
            } else {
                output << 10 << " " 
                       << 1 << " " 
                       << lrand(1, 30) << " " 
                       << 1 << " " 
                       << lrand(1, 30) <<endl;
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
