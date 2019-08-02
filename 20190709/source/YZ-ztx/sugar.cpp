#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 5000010;
int n;
char s[maxn], info[maxn];
int ans = 0;

inline void file()
{
	freopen("sugar.in", "r", stdin);
	freopen("sugar.out", "w", stdout);
}

class Trie
{
	private:
		int ch[maxn][2], fail[maxn], tot;
		bool End[maxn];
		
	public:
		inline void Clear()
		{
			tot = 0;
			memset(ch, 0, sizeof(ch));
			memset(End, false, sizeof(End));
		}
		
		inline void Add(char *s)
		{
			int u = 0, len = strlen(s);
			for (int i = 0, id; i < len; ++i)
			{
				id = s[i] - '0';
				if (!ch[u][id]) ch[u][id] = ++tot;
				u = ch[u][id];
			}
			End[u] = true;
		}
		
		inline void Build()
		{
			queue<int> q;
			register int i;
			for (i = 0; i < 2; ++i)
			{
				if (ch[0][i]) 
				{
					q.push(ch[0][i]);
					fail[ch[0][i]] = 0;
				}
			}
			int u;
			while (!q.empty())
			{
				u = q.front();
				for (i = 0; i < 2; ++i)
				{
					if (ch[u][i])
					{
						fail[ch[u][i]] = ch[fail[u]][i];
						q.push(ch[u][i]);
					}
					else ch[u][i] = ch[fail[u]][i];
				}
				q.pop();
			}
		}
		
		void dfs(char *s, int len, int u, int i, int res)
		{
			if (i == len) 
			{
				ans = max(ans, res);
				return;
			}
			int id = s[i] - '0';
			if (End[ch[u][id]]) 
				dfs(s, len, 0, i + 1, res + 1);
			dfs(s, len, ch[u][id], i + 1, res);
		}
}AC;

int main()
{
	file();
	scanf("%d", &n);
	scanf("%s", info);
	AC.Clear();
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", s);
		AC.Add(s);
	}
	AC.Build();
	AC.dfs(info, strlen(info), 0, 0, 0);
	printf("%d", ans);
	return 0;
}
