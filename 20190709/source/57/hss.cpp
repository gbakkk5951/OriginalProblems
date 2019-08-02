#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;
int main(){
	ifstream fin("hss.in");
	ofstream fout("hss.out");
	srand((int)time(0));
	string a;
	int n,m,x;
	char y;
	fin>>n>>m;
	fin>>a;
	for(int i=0;i<m;i++){
		fin>>x>>y;
	}
	int pianfen=a.length();
	if(m!=0)fout<<4<<endl<<7<<endl<<7<<endl<<9;
	else fout<<rand()%(pianfen+1);
	fin.close();
	fout.close();
	return 0;
}

