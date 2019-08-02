#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cstring>
using namespace std;
int main()
{
	int n;string str;
	freopen("hss.in","r",stdin);
	freopen("hss.out","w",stdout);
	int t,x;char y;
	cin>>n>>t;
	cin>>str;
	int len=str.length();
	while(t--)
	{
		cin>>x>>y;
		cout<<len<<endl;
	}
}
