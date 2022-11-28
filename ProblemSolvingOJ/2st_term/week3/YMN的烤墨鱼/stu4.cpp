#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<pil> vpil;

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define FOR(_, l, r) for (int _ = l; _ <= r; _++)
#define ROF(_, r, l) for (int _ = r; _ >= l; _--)
#define MP make_pair
#define Umin(a, b) a = min(a, b)
#define Umax(a, b) a = max(a, b)

const int N = 2e6 + 5;
const ll linf = 1e18;

vi num(N);
vi last(N);
vll factorial(15);

ll fac(int x)
{
	if (x > 13)
		return linf;
	if (factorial[x])
		return factorial[x];
	return factorial[x] = x * fac(x - 1);
}

int find(int l, int r, int x)
{
	if (l >= r - 1)
		return (last[l] >= x) ? l : r;
	int mid = (l + r) / 2;
	last[mid] >= x ? r = mid : l = mid;
	return find(l, r, x);
}

ll upper(int n)
{
	ll ans = 1;
	vb used(15);
	vi temp(15);
	int top, cnt, start, tmp;
	start = max(n - 12, 1);
	FOR (i, start, n)
		temp[i - start + 1] = num[i];
	sort(temp.begin() + 1, temp.begin() + n - start + 2);
	FOR (i, start, n)
	{
		top = min(n, 13);
		while (used[top])
			top--;
		cnt = 0;
		FOR (j, 1, 13)
			if (temp[j] == num[i])
				tmp = j;
		used[tmp] = true;
		ROF(j, top, tmp)
			if (!used[j])
				cnt++;
		ans += cnt * fac(n - i);
	}
	return ans;
}

void arrange(int n, int start, ll k)
{
	vb used(15);
	int pos, cnt;
	FOR (i, start, n)
	{
		pos = 1;
		while (used[pos])
			pos++;
		cnt = k / fac(n - i);
		k %= fac(n - i);
		while (cnt)
		{
			if (!used[pos])
				cnt--;
			pos++;
		}
		while (used[pos])
			pos++;
		num[i] = last[pos];
		used[pos] = true;
	}
	return;
}

void solve(int n, ll k)
{
	int tmp;
	ll up = upper(n);
	if (n <= 13)
	{
		k = (k + fac(n) - up) % fac(n);
		FOR (i, 1, n)
		{
			num[i] = i;
			last[i] = i;
		}
	}
	else
	{
		FOR (i, 1, 13)
			last[i] = num[n - 13 + i];
		sort(last.begin() + 1, last.begin() + 14);
		if (k >= up)
		{
			tmp = 13;
			while (num[n - tmp] > last[tmp])
			{
				last[tmp + 1] = num[n - tmp];
				tmp++;
			}
			if (tmp == n)
			{
				FOR (i, 1, n)
					num[i] = i;
				FOR (i, 1, 13)
					last[i] = n - 13 + i;
			}
			else
			{
				swap(num[n - tmp], last[find(1, tmp, num[n - tmp])]);
				FOR (i, 1, tmp)
					num[n - tmp + i] = last[i];
				FOR (i, 1, 13)
					last[i] = num[n - 13 + i];
			}
		}
		k = (k + fac(13) - up) % fac(13);
	}
	arrange(n, max(n - 12, 1), k);
	FOR (i, 1, n)
		cout << num[i] << " ";
	cout << endl;
}

int main()
{
	fastio;
	factorial[0] = 1;
	int t, n;
	ll k;
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		FOR (i, 1, n)
			cin >> num[i];
		solve(n, k);
	}
	return 0;
}
