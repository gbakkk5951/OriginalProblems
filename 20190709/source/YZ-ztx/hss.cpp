#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1000010;
int n, m;
char s[maxn << 1];

struct Node
{
	int L, R, key;
		
	Node(int l, int r, int val) : L(l), R(r), key(val) {}

	Node() {}
};
		
class my_list
{
	private:
		Node node[maxn << 1];
	
	public:
		int tot;
		
		inline void Init()
		{
			tot = 1;
			node[0].L = -1, node[1].R = -1;
			node[0].R = 1, node[1].L = 0;
		}
	
		inline void Insert(int x, int pos)
		{
			if (pos == 0)
			{
				++tot;
				node[tot].key = x;
				node[tot].R = node[0].R;
				node[tot].L = 0;
				node[0].R = tot;
				return;
			}
			if (pos == 1)
			{
				++tot;
				node[tot].key = x;
				node[tot].L = node[1].L;
				node[tot].R = 1;
				node[1].L = tot;
				return;
			}
			int newpos = 0;
			for (int i = node[0].R; i != 1; i = node[i].R)
			{
				++newpos;
				if (newpos == pos)
				{
					++tot;
					node[tot].key = x;
					node[tot].L = node[i].L;
					node[tot].R = i;
					node[i].L = tot;
					break;
				}
			}
		}
		
		inline int Find(int pos)
		{
			int newpos;
			if (pos < tot / 2)
			{
				newpos = 0;
				for (int i = node[0].R; i != 1; i = node[i].R)
				{
					++newpos;
					if (newpos == pos)
						return node[i].key;
				}
			}
			else 
			{
				newpos = tot;
				for (int i = node[1].L; i != 0; i = node[i].L)
				{
					--newpos;
					if (newpos == pos)
						return node[i].key;
				}
			}
		}
}H, S;

int main()
{
	freopen("hss.in", "r", stdin);
	freopen("hss.out", "w", stdout);
	H.Init(), S.Init();
	scanf("%d%d", &n, &m);
	scanf("%s", s);
	int sickle = 0, hammer = 0, ans = 0, minl = 0, maxr;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == 's') 
		{
			S.Insert(i, 1);
			if (maxr < i) 
			{
				minl = i;
				sickle = 0;
			}
			++sickle;
		}
		else if (s[i] == 'h') 
		{
			if (sickle) 
			{
				H.Insert(i, 1);
				--sickle;
				maxr = i;
			}
			else ++hammer;
		}
	}
	int pos = max(sickle, hammer) - abs(sickle - hammer);
	printf("%d\n", rand());
	int x, ls, rs, lh, rh = hammer;
	while (m--)
	{
		scanf("%d%s", &x, s);
		if (s[0] == 's')
		{
			if (hammer) ++ans;
			else ++sickle;
		}
		else if (s[0] == 'h')
		{
			
		}
		printf("%d\n", rand());
	}
	return 0;
}
