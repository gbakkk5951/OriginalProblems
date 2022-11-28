#include <bits/stdc++.h>
using namespace std;
struct sweet
{
  int ty;
  long long sum;
  sweet *l, *r;
} a[2000005];
int ty[1000005];
long long val[1000005];
sweet *lh, *rh;
long long ans;
void add(int pos, int type, long long value)
{
  if (pos == 0)
  {
    sweet *now = lh;
    if (type == 2)
    {
      now->sum += value;
      ans = max(ans, value);
      if (now->ty == 2)
        ans = max(ans, now->sum);
    }
    else if (type == 0)
    {
      if (now->ty == 1)
      {
        now->ty = 2;
        now->sum += value;
        ans = max(ans, now->sum);
        if (now->r != NULL)
        {
          now->sum += (now->r)->sum;
          now->ty = (now->r)->ty;
          now->r = (now->r)->r;
        }
        else
        {
          rh = now;
        }
        if (now->ty == 2)
          ans = max(ans, now->sum);
      }
      else if (now->ty == 0)
      {
        sweet *x = new (sweet);
        x->ty = 0;
        x->sum = value;
        x->l = NULL;
        x->r = now;
        now->l = x;
        lh = x;
      }
      else
      {
        now->ty = 0;
        now->sum += value;
      }
    }
    else
    {
      if (now->ty == 1)
      {
        sweet *x = new (sweet);
        x->ty = 1;
        x->sum = value;
        x->l = NULL;
        x->r = now;
        now->l = x;
        lh = x;
      }
      else if (now->ty == 0)
      {
        sweet *x = new (sweet);
        x->ty = 1;
        x->sum = value;
        x->l = NULL;
        x->r = now;
        now->l = x;
        lh = x;
      }
      else
      {
        now->ty = 1;
        now->sum += value;
      }
    }
  }
  if (pos == 1)
  {
    sweet *now = rh;
    if (type == 2)
    {
      now->sum += value;
      ans = max(ans, value);
      if (now->ty == 2)
        ans = max(ans, now->sum);
    }
    else if (type == 1)
    {
      if (now->ty == 0)
      {
        now->ty = 2;
        now->sum += value;
        ans = max(ans, now->sum);
        if (now->l != NULL)
        {
          now->sum += (now->l)->sum;
          now->ty = (now->l)->ty;
          now->l = (now->l)->l;
        }
        else
        {
          lh = now;
        }
        if (now->ty == 2)
          ans = max(ans, now->sum);
      }
      else if (now->ty == 1)
      {
        sweet *x = new (sweet);
        x->ty = 1;
        x->sum = value;
        x->l = now;
        x->r = NULL;
        now->r = x;
        rh = x;
      }
      else
      {
        now->ty = 1;
        now->sum += value;
      }
    }
    else
    {
      if (now->ty == 1)
      {
        sweet *x = new (sweet);
        x->ty = 0;
        x->sum = value;
        x->l = now;
        x->r = NULL;
        now->r = x;
        rh = x;
      }
      else if (now->ty == 0)
      {
        sweet *x = new (sweet);
        x->ty = 0;
        x->sum = value;
        x->l = now;
        x->r = NULL;
        now->r = x;
        rh = x;
      }
      else
      {
        now->ty = 0;
        now->sum += value;
      }
    }
  }
}
int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &ty[i]);
  for (int i = 1; i <= n; i++)
    scanf("%lld", &val[i]);
  lh = new (sweet);
  rh = new (sweet);
  if (n == 0)
  {
    printf("0\n");
    int x;
    scanf("%d%d%lld", &x, &ty[1], &val[1]);
    lh->ty = ty[1];
    lh->sum = val[1];
    lh->l = lh->r = NULL;
    if (ty[1] == 2)
      ans = val[1];
    rh = lh;
    m--;
  }
  else
  {
    lh->ty = ty[1];
    lh->sum = val[1];
    lh->l = lh->r = NULL;
    if (ty[1] == 2)
      ans = val[1];
    rh = lh;

    for (int i = 2; i <= n; i++)
      add(1, ty[i], val[i]);
  }
  printf("%lld\n", ans);

  while (m--)
  {
    int op, typ;
    long long value;
    scanf("%d%d%lld", &op, &typ, &value);
    add(op, typ, value);
    printf("%lld\n", ans);
  }
  return 0;
}
