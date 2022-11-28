#include <bits/stdc++.h>
using namespace std;
int n, a[55][55], tag[55], ans, deep, goo[55];
long long num[55];
void solve(int x)
{
  goo[x] = 1;
  for (int i = 1; i <= n; i++)
    if (a[x][i] && !goo[i])
      solve(i);
}
int main()
{
  int T;
  cin >> T;
  while (T--)
  {
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
      tag[i] = num[i] = goo[i] = 0;
      for (int j = 1; j <= n; j++)
      {
        cin >> a[i][j];
        num[i] += (a[i][j] << j);
      }
    }
    ans = 1;
    for (int i = 1; i <= n && ans; i++)
      if (!a[i][i])
      {
        ans = 0;
      }
    if (!ans)
    {
      cout << "N" << endl;
      continue;
    }
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++)
        if (num[i] == num[j])
          tag[j] = 1;
    for (int i = 1; i <= n && ans; i++)
      for (int j = 1; j <= n && ans; j++)
        for (int k = 1; k <= n && ans; k++)
          if (i != j && j != k && i != k)
            if (a[i][j] && a[j][k] && (!a[i][k]))
              ans = 0;
    if (!ans)
    {
      cout << "N" << endl;
      continue;
    }
    for (int i = 1; i < n && ans; i++)
      for (int j = i + 1; j <= n && ans; j++)
        if ((!tag[i]) && (!tag[j]))
        {
          if (a[i][j] || a[j][i])
            continue;
          int tmp = 0;
          for (int k = 1; k <= n; k++)
            if (k != i && k != j && (!tag[k]))
              if (a[k][i] && a[k][j])
              {
                tmp++;
                goo[tmp] = k;
              }

          if (tmp == 0)
            ans = 0;
          int dd = 0;
          for (int k = 1; k <= tmp; k++)
          {
            int d = 1;
            for (int l = 1; l <= tmp; l++)
              if (l != k)
              {
                if (!a[l][k])
                  d = 0;
              }
            if (d)
              dd = 1;
          }
          if (!dd)
            ans = 0;
        }
    for (int i = 1; i < n && ans; i++)
      for (int j = i + 1; j <= n && ans; j++)
        if ((!tag[i]) && (!tag[j]))
        {
          if (a[i][j] || a[j][i])
            continue;
          int tmp = 0;
          for (int k = 1; k <= n; k++)
            if (k != i && k != j && (!tag[k]))
              if (a[i][k] && a[j][k])
              {
                tmp++;
                goo[tmp] = k;
              }

          if (tmp == 0)
            ans = 0;
          int dd = 0;
          for (int k = 1; k <= tmp; k++)
          {
            int d = 1;
            for (int l = 1; l <= tmp; l++)
              if (l != k)
              {
                if (!a[k][l])
                  d = 0;
              }
            if (d)
              dd = 1;
          }
          if (!dd)
            ans = 0;
        }
    if (ans)
      cout << "Y" << endl;
    else
      cout << "N" << endl;
  }

  return 0;
}
