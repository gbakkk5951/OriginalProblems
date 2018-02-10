using namespace std;
int main(){}
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<windows.h>
const int m=1;
const string orgname[]={"Êý¾Ý_ex"};
const string newname[]={"tour_ex"};
const int beg[]={0};
const int end[]={24};
const char BeginFrom1 = false;
struct _Main{

string to_string(int a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}

string src,dst;
_Main(){
	int i,j;
	for(j=0;j<m;j++){
		for(i=beg[j];i<=end[j];i++){
			src=orgname[j]+to_string(i)+".in";
			dst=newname[j] + to_string(i+BeginFrom1 * (beg[j]==0)) + ".in";
			rename(src.c_str(),dst.c_str());
			src=orgname[j]+to_string(i)+".out";
			dst=newname[j] + to_string(i+BeginFrom1 * (beg[j]==0)) + ".out";
			rename(src.c_str(),dst.c_str());		
		}		
		
	}


}	
	
	
}Maker;
