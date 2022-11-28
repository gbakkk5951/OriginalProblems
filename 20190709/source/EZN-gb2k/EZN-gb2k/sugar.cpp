#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;
string str,s;
int n;
int main()
{
	freopen("sugar.in","r",stdin);
	freopen("sugar.out","w",stdout);
	cin>>n;
	cin>>str;
	int a=str.length();
	int mi;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		int lenn=s.length();
		mi=min(mi,lenn);
	}
	cout<<a/mi;
}
