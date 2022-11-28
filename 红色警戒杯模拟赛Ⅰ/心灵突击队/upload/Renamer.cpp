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
const string problemname[]={"commando"};
const int beg[]={0};
const int end[]={24};
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
			src=problemname[j]+to_string(i)+".in";
			dst=to_string(i+(beg[j]==0))+".in";
			rename(src.c_str(),dst.c_str());
			src=problemname[j]+to_string(i)+".out";
			dst=to_string(i+(beg[j]==0))+".out";
			rename(src.c_str(),dst.c_str());		
		}		
		
	}


}	
	
	
}Maker;
