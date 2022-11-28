#include <bits/stdc++.h>
using namespace std;
int main() {
    long long & (deque<long long>::*end)() = NULL; 
	int pos = rand() & 1;
	
	end = pos ? (long long & (deque<long long>::*)()) (&deque<long long>::back) 
	  	      : (long long & (deque<long long>::*)()) (&deque<long long>::front);
	
}

