#include <bits/stdc++.h>
#define AC 0
#define WA 1
using namespace std;
typedef long long lld;


int main(int argc, char *argv[])
{
	FILE *f_in = fopen(argv[1], "r");
	FILE *f_out = fopen(argv[3], "r");
	FILE *f_user = fopen(argv[2], "r");


	fclose(f_in);
	fclose(f_out);
	fclose(f_user);
	printf("%d\n", Score);
	return AC;
}
