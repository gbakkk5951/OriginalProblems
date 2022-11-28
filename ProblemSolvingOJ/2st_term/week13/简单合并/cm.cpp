#include <bits/stdc++.h>
using namespace std;
char in[50], out[50];
char cmd[100];
const int maxn = 1e6 + 10;
int size[128];
int arr[maxn];
int tag[maxn];
int beg[maxn];
void make(int I) {
	FILE *filename = fopen(in, "w");
	int n = 1e6, k = I & 1 ? 31 : (1 + rand() % 31);
	if (I < 5) n = 130 + rand() % 500;
	int m = n;
	memset(tag, 0, sizeof(tag));
	for (int i = 1; i <= k - 1; ++i){
		tag[i] = 1;
	}
	
	random_shuffle(tag + 1, tag + n);
	tag[n] = 1;
	int index = 0;
	beg[++index] = 1;
	
	for (int i = 1; i <= n; ++i) {
		arr[i] = (int)-1e9 + (((unsigned)rand() ^ ((unsigned)rand() << 15) ^ ((unsigned)rand() << 30)) % (unsigned)(2e9 + 1));
		if (tag[i]) {
			size[index] = i - beg[index] + 1;
			if (rand() & 1) {
				sort(arr + beg[index], arr + beg[index] + size[index], greater<int>());	
			} else {
				sort(arr + beg[index], arr + beg[index] + size[index], less<int>());
			}
			beg[++index] = i + 1;
		}
	}
	fprintf(filename, "%d %d", k, m);
	index = 1;
	for (int i = 1; i <= n; ++i) {
		if (i == beg[index]) {
			fprintf(filename, "\n%d ", size[index]);
		} 
		fprintf(filename, "%d ", arr[i]);
		index += i == beg[index] + size[index] - 1;
 	}
	fclose(filename);
}
int main() {
	srand(time(0));
	for (int I = 0; I < 10; ++I) {
		sprintf(in, "data%d.in", I);
		sprintf(out, "data%d.out", I);
		sprintf(cmd, "std.exe > %s < %s", out, in);
		printf("make %d\n", I);
		fflush(stdout);
//		make(I);
		system(cmd);
		printf("%d Finished\n", I);
		fflush(stdout);
	}
}
