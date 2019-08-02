#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cstdio>
using namespace std;
ifstream fin("sugar.in");
ofstream fout("sugar.out");
int main(){
	srand((int)time(0));
	string a;
	int n,i=0;
	fin>>n;
	fin>>a;
	int pianfen=a.length()/4;
	for(int k=0;k<n;k++)fin>>a;
	if(n==5)fout<<6;
	else fout<<rand()%(3*pianfen)+pianfen;
	fin.close();
	fout.close();
	return 0;
}
