#include <bits/stdc++.h>
using namespace std;
int s[1005], n, m[1005], sum[1005];
bool warning;
bool check(int p, int x)
{
  if (p < 0 || p >= sum[n])
  {
    return false;
  }
  if (sum[x] > p || p >= sum[x + 1])
  {
    warning = true;
  }
  return true;
}
int main()
{
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> m[i];
    sum[i + 1] += m[i] + sum[i];
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m[i]; j++)
      cin >> s[sum[i] + j];
  int T;
  cin >> T;
  while (T--)
  {
    //		for(int i=0;i<sum[n];i++)cout<<s[i]<<" ";
    //		cout<<endl;
    int op, x, y, x1, y1, v, c;
    warning = 0;
    cin >> op;
    if (op == 0)
    {
      cin >> x >> y >> v >> c;
      if (c == 0)
      {
        cout << "true" << endl;
        continue;
      }
      if ((!check(sum[x] + y + c - 1, x)) || (!check(sum[x] + y, x)))
        cout << "overflow" << endl;
      else
      {
        if (warning)
          cout << "w";
        for (int i = sum[x] + y; i <= sum[x] + y + c - 1; i++)
          s[i] = v;
        cout << "true" << endl;
      }
    }
    if (op == 1)
    {
      cin >> x >> y >> x1 >> y1;
      int ed = -1, bj = 0;
      for (int i = sum[x] + y; (ed == -1) && (!bj); i++)
      {
        if (!check(i, x))
          bj = 1;
        if (s[i] == 0)
        {
          ed = i;
        }
      }
      for (int i = sum[x1] + y1; i <= sum[x1] + y1 + (ed - sum[x] - y); i++)
        if (!check(i, x1))
          bj = 1;
      if (bj)
      {
        cout << "overflow" << endl;
        continue;
      }
      if (sum[x1] + y1 == sum[x] + y)
      {
        cout << "overwrite" << endl;
        continue;
      }
      if (sum[x1] + y1 < sum[x] + y)
        if (sum[x1] + y1 + (ed - sum[x] - y) >= sum[x] + y)
        {
          cout << "overwrite" << endl;
          continue;
        }
      if (sum[x1] + y1 > sum[x] + y)
        if (ed >= sum[x1] + y1)
        {
          cout << "overwrite" << endl;
          continue;
        }

      if (warning)
        cout << "w";
      for (int i = sum[x1] + y1; i <= sum[x1] + y1 + (ed - sum[x] - y); i++)
        s[i] = s[sum[x] + y + (i - sum[x1] - y1)];
      cout << "true" << endl;
    }
    if (op == 2)
    {
      cin >> x >> y;
      if (!check(sum[x] + y, x))
        cout << "overflow" << endl;
      else
      {
        int ans = 0, bj = 0;
        for (int i = sum[x] + y; !bj; i++)
        {
          if (!check(i, x))
          {
            cout << "overflow" << endl;
            ans = -1;
          }
          if (s[i] == 0)
            bj = 1;
          else
            ans++;
        }
        if (ans != -1)
        {
          if (warning)
            cout << "w";
          cout << ans << endl;
        }
      }
    }
  }
  return 0;
}
