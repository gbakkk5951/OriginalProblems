#include <iostream>
using namespace std;

typedef long long ll;
typedef struct _COORD
{
    int X;
    int Y;
} COORD;

ll cnt = 0;
inline int read();
inline void out(ll);
bool judge(COORD, COORD);
void merge(COORD *, int, int, int);
void merge_sort(COORD *, int, int);

    COORD p[600000];
int main()
{
    int N;
    N = read();
    for (int i = 1; i <= N; i++)
    {
        int x, y;
        x = read();
        y = read();
        p[i] = {x, y};
    }
    merge_sort(p, 1, N);
    cnt += (N - 1);
    out(cnt);
    return 0;
}

inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

inline void out(ll a)
{
    if (a >= 10)
        out(a / 10);
    putchar(a % 10 + '0');
}

bool judge(COORD a, COORD b)
{
    if (a.X < b.X)
        return true;
    else if (a.X > b.X)
        return false;
    else
        return (a.Y < b.Y ? true : false);
}

void merge(COORD *p, int l, int m, int r)
{
    COORD *temp = new COORD[r - l + 1];
    int i = 0;
    int left = l;
    int right = m + 1;
    while (left <= m && right <= r)
    {
        if (judge(p[left], p[right]))
        {
            temp[i++] = p[left++];
        }
        else
        {
            cnt += (ll)(2 * (m - left + 1));
            if (left == 1)
                cnt -= (ll)1;
            temp[i++] = p[right++];
        }
    }
    while (left <= m)
    {
        temp[i++] = p[left++];
    }
    while (right <= r)
    {
        temp[i++] = p[right++];
    }
    for (i = 0; i < r - l + 1; i++)
    {
        p[l + i] = temp[i];
    }
    delete []temp;
}

void merge_sort(COORD *p, int l, int r)
{
    if (l == r)
        return;
    int m = (l + r) / 2;
    merge_sort(p, l, m);
    merge_sort(p, m + 1, r);
    merge(p, l, m, r);
}

