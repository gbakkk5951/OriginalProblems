using namespace std;
#include<bits/stdc++.h>

struct _Main{
//////////////
string dataName = "commando";
string stdName = "std";
string bruteName = "brute";

bool make_data = true;
bool run_ans = true;

int beg = 20
,   end = 25
,   exbeg = 0
,   exend = 0
;

bool check_brute = true;
bool check_out_pause = true;
bool loop_check = true;
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
	int a, b, c, d;
	int mod = 1e7;
	int m, xmin, ymin, xmax, ymax;
	int maxpos;
	for(I=beg;I<end;I++){
		outfile=dataName+to_string(I)+".in";
		cerr<<"Make "<<outfile<<endl;
		ofstream output(outfile.c_str());
		m=10000;maxpos=1e8;
        xmin = lrand(-mod, mod);
        ymin = lrand(-mod, mod);
        switch (I) {
            case 20:{
                xmax = xmin;
                ymax = ymin + 4e6 - 1;
            	break;
            }
            case 21:{
                xmax = xmin + 4e6 - 1;
                ymax = ymin;
            	break;
            }            
            case 22:{
                xmax = xmin + 400 - 1;
                ymax = ymin + 1e4 - 1;
            	break;
            }            
            case 23:{
                xmax = xmin + 2e3 - 1;
                ymax = ymin + 2e3 - 1;
            	break;
            }
            case 24:{
                xmax = xmin + 2e3 - 1;
                ymax = ymin + 2e3 - 1;
            	break;
            }            
        }
        
        
		output<<m<<" "<<xmin<<" "<<ymin<<" "<<xmax<<" "<<ymax<<endl;
		for(i=0;i<m;i++){
			if(rand()&1){
				if(rand()%3 && (I == 24 ? (rand()%3 == 1) : 1)){//Õ¨µ¯ 
					if(rand()%4<2){//ÄÚ²¿ 
						a=xmin+lrand()%(xmax-xmin+1);b=ymin+lrand()%(ymax-ymin+1);
						output<<1<<" "<<a<<" "<<b<<" "
						<<lrand()%(int)min(ymax-ymin+1,xmax-xmin+1)+(rand()%100)*(rand()%5==1) + 1
						<<" "<<lrand()%(int)1e4<<endl;
					}else if(rand()%4<2){//±ßÔµÕ¨ 
						if(rand()&1)a=xmax-rand()%500;
						else a=xmax+rand()%500;
						if(rand()&1)b=xmax-rand()%500;
						else b=xmax+rand()%500;	
						output<<1<<" "<<a<<" "<<b<<" "
						<<lrand()%(int)1000+(rand()%100)*(rand()%5==1) + 1
						<<" "<<lrand()%(int)1e4<<endl;													
					}
					else{//ÂÒÕ¨ 
						output<<1<<" "<<lrand()%(maxpos+1)*randsym()<<" "<<lrand()%(maxpos+1)*randsym()<<" "
						<<lrand()%(int)1e8 + 1<<" "<<lrand()%(int)1e4<<endl;
					}
				}else{//Ï´Ïû 
    				a=lrand()%(xmax-xmin+1);
    				c=lrand()%(ymax-ymin+1);			    
    				
                    if (rand()%13 == 1) {
                        b=lrand()%(xmax-xmin+1-a);
        				d=lrand()%(ymax-ymin+1-c);					    
    				    b = min (b, rand()%10 + 2);
    				    d = min (d, rand()%10 + 2);
    				} else if (rand()%7 == 1) {
    				    if (rand()%3 == 1) {
    				        b = xmax-xmin-a;
    				        d = 0;
    				    } else if (rand()%3 == 1){
    				        b = 0;
    				        d = ymax-ymin-c;
    				    } else {
    				        b = xmax-xmin-a;
    				        d = ymax-ymin-c;
    				    }
    				} else {
        				b=lrand()%(xmax-xmin+1-a);
        				d=lrand()%(ymax-ymin+1-c);				    
    				}
					output<<2<<" "<<xmin+a<<" "<<ymin+c<<" "<<xmin+a+b<<" "<<ymin+c+d<<" "<<lrand()%(int)1e4<<endl;						
				}
				
			}else{
				a=lrand()%(xmax-xmin+1);
				c=lrand()%(ymax-ymin+1);			    
				if (rand()%13 == 1) {
                    b=lrand()%(xmax-xmin+1-a);
    				d=lrand()%(ymax-ymin+1-c);					    
				    b = min (b, rand()%10 + 2);
				    d = min (d, rand()%10 + 2);
				} else if (rand()%7 == 1) {
				    if (rand()%3 == 1) {
				        b = xmax-xmin-a;
				        d = 0;
				    } else if (rand()%3 == 1){
				        b = 0;
				        d = ymax-ymin-c;
				    } else {
				        b = xmax-xmin-a;
				        d = ymax-ymin-c;
				    }
				} else {
    				b=lrand()%(xmax-xmin+1-a);
    				d=lrand()%(ymax-ymin+1-c);				    
				}

				output<<0<<" "<<xmin+a<<" "<<ymin+c<<" "<<xmin+a+b<<" "<<ymin+c+d<<" "<<endl;				
				
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
