using namespace std;
#include <cstdio>
#include<fstream>
#include<iostream>
#include<string>
#include<bitset>
#define ac 0
#define wa 1

string type;
string num[505],ans;
int n,m,bitlen;


int main(int argc,char *args[])  
{
	int i,j,k;
	char oper;
	ifstream f_in(args[1]);
	ifstream f_out(args[2]);
	ifstream f_user(args[3]);
	f_out>>type;
	int n;
	int a,b;
	if(type != "No"){
		f_in>>n;
		f_in>>m>>bitlen;
		for(i=1;i<=n;i++){
			if(!(f_user>>num[i]) || num[i].length()!=bitlen){
				return wa;
			}
			for(j=0;j<bitlen;j++){
				if(num[i][j]!='0' && num[i][j]!='1')return wa;
			}
		}
		if(f_user>>num[i]){
			return wa;
		}
		for(i=1;i<=m;i++){
			f_in>>a;f_in>>oper;f_in>>b;f_in>>ans;
			if(oper=='^'){
				for(j=0;j<bitlen;j++){
					if(( (num[a][j]-'0')^(num[b][j]-'0') ) != (ans[j]-'0')){
						return wa;
					}
				}						
			}else if(oper=='|'){
				for(j=0;j<bitlen;j++){
					if(( (num[a][j]-'0')|(num[b][j]-'0') ) != (ans[j]-'0')){
						return wa;
					}
				}						
			}else if(oper=='&'){
				for(j=0;j<bitlen;j++){
					if(( (num[a][j]-'0')&(num[b][j]-'0') ) != (ans[j]-'0')){
						return wa;
					}
				}				
			}
		}
	}else if(!(f_user>>type) || type!="No" || (f_user>>type)){
		return wa;
	}
    return ac;  
}  
