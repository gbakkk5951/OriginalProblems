#include <bits/stdc++.h>
using namespace std;

namespace lky
{
const int MAXN = 1e6 + 1;
size_t n, m;
struct node
{
    char c;
    node *prev, *nxt;
};
node *head, *tail, *q, *now;
void initialize()
{
    head = new node();
    tail = new node();
    head->nxt = tail;
    tail->prev = head;
}
void insert(int f, char c)
{
    if (f == 1)
    {
        q = new node();
        q->c = c;
        head->nxt->prev = q;
        q->nxt = head->nxt;
        head->nxt = q;
        q->prev = head;
    }
    if (f == 2)
    {
        q = new node();
        q->c = c;
        tail->prev->nxt = q;
        q->prev = tail->prev;
        tail->prev = q;
        q->nxt = tail;
    }
}
inline void test()
{
    for (now = head->nxt; now != tail; now = now->nxt)
        cerr << now->c;
    cerr << endl;
}
char stack[MAXN << 1 | 1];
size_t point;
void sov()
{
    int ans = 0;
    memset(stack, 0, sizeof(stack));
    for (now = head->nxt; now != tail; now = now->nxt)
    {
        stack[++point] = now->c;
        if (stack[point] == 'h')
            for (size_t i = point; i >= 1; --i)
            {
                if (stack[i] == 's')
                {
                    ans += (point - i + 1);
                    point = i + 1;
                    goto end;
                }
            }
    end:;
    }
    for (register int i = point; i >= 1; i--)
    {
        if (stack[i] == 'S')
            ans++;
        else
            goto R;
    }
R:
    printf("%d\n", ans-1);
    return;
}
signed _main()
{
    cin >> n >> m;
    initialize();
    for (size_t i = 1; i <= n; i++)
    {
        char s = getchar();
        while (s != 's' && s != 'S' && s != 'h')
            s = getchar();
        insert(2, s);
    }
    sov();
    for (register size_t i = 1; i <= m; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        char s = getchar();
        while (s != 's' && s != 'S' && s != 'h')
            s = getchar();
        insert(tmp, s);
        // test();
        sov();
    }
    return 0;
}
} // namespace lky

int main()
{
#ifdef lky233
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#else
    freopen("hss.in", "r", stdin);
    freopen("hss.out", "w", stdout);
#endif
    lky::_main();
    fclose(stdin);
    fclose(stdout);
    return 0;
}