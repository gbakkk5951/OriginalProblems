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
const string problemname="bit";

struct _Main{

string to_string(int a){
	stringstream os;string ans;
	os<<a;
	os>>ans;
	return ans;
}

string src,dst;
_Main(){
	int i;
	for(i=1;i<=20;i++){
		src=problemname+to_string(i)+".in";
		dst=to_string(i)+".in";
		rename(src.c_str(),dst.c_str());
		src=problemname+to_string(i)+".out";
		dst=to_string(i)+".out";
		rename(src.c_str(),dst.c_str());		
		
	}

}	
	
	
}Maker;
