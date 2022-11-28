#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int cnt;
int X;
int ans = 0;
void dfs(int depth, int currentAns)
{
	++cnt;
	if (depth == X + 1)
	{
		ans += X - currentAns;
		return;
	}

	int up = (X - currentAns) / depth;
    if (up == 0) {ans += X - currentAns; return;}
  for (int i = 0; i <= up; i++)
    dfs(depth + 1, currentAns + i * depth);
}

int main()
{
	
  scanf("%d", &X);
  dfs(1, 0);
  printf("%d", cnt);
  return 0;
}
