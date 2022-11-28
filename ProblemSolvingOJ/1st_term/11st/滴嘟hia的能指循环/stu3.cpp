#include <bits/stdc++.h>
using namespace std;
int d[100005], bj[100005], n, ans, tag[100005], st;
void dfs(int now, int leng)
{
  if (bj[now])
  {
    //		cout<<now<<"s"<<leng<<endl;
    if (now == st)
    {
      ans += leng;
      tag[now] = 1;
    }

    return;
  }
  //	cout<<now<<"s"<<leng<<"s"<<tag<<endl;
  bj[now] = 1;
  if (tag[d[now]])
  {
    bj[now] = 0;
    return;
  }
  dfs(d[now], leng + 1);
  //	cout<<now<<"s"<<leng<<"s"<<tag<<endl;
  if (!tag[d[now]])
    bj[now] = 0;
  else
    tag[now] = 1;
}
int main()
{
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> d[i];
  for (int i = 1; i <= n; i++)
    if (!tag[i])
    {
      st = i;
      dfs(i, 0);
    }
  cout << ans;
  return 0;
}
