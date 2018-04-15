#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;
int _TimeWatcherArray_[150010];
struct _TimeWatcherType_{

	~_TimeWatcherType_(){
		Print();
	}
	void  inline operator () (){
		Print();
	}
	void Print(){
		ofstream output("RunningResult.res");
		output<<_TimeWatcherCount_<<endl;
		int i;
		for(i=1;i<=_TimeWatcherCount_;i++){
			output<<_TimeWatcherArray_[i]<<endl;
		}
		output.close();
	}
	
}_TimeWatcher_;





