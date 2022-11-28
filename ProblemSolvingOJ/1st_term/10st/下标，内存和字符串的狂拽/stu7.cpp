#include <iostream>
#define N 1005
using namespace std;
int length[N];
int start_length[N];
char A[N];
int n;
bool warning;
bool check(int p, int x) // p是当前字符编号，x是p所在的字符串
{
    if (p < 0 || p > start_length[n - 1] + length[n - 1] - 1) //非法访问
        return false;
    else
    {
        if (x == n - 1)
        {
            if (p < start_length[x])
                warning = true;
        }
        else if (p < start_length[x] || p >= start_length[x + 1]) //合法越界
            warning = true;
        return true;
    }
}
void memset(int x, int y, int v, int c)
{
    warning = false;
    if (c == 0)
        cout << "true" << endl;
    else
    {
        if (check(start_length[x] + y, x) == false || check(start_length[x] + y + c - 1, x) == false)
            cout << "overflow" << endl;
        else
        {
            for (int i = 0; i < c; i++)
                A[start_length[x] + y + i] = v;
            if (warning == true)
                cout << "wtrue" << endl;
            else
                cout << "true" << endl;
        }
    }
}
int strlen(int x, int y)
{
    warning = false;
    int i = 0, j = 0;
    while (check(start_length[x] + y + j, x) == true && A[start_length[x] + y + j] != '0') //考虑的&&的最优判断，一旦前者为假，整个为假。
    {
        i++;
        j++;
    }
    return i;
} //该长度不包括末尾0
void strcpy(int x, int y, int x0, int y0)
{
    warning = false;
    if (check(start_length[x] + y, x) == false || check(start_length[x0] + y0, x0) == false || check(start_length[x] + y + strlen(x, y), x) == false || check(start_length[x0] + y0 + strlen(x, y), x0) == false)
        cout << "overflow" << endl;
    else
    {
        if ((start_length[x0] + y0 >= start_length[x] + y && start_length[x0] + y0 <= start_length[x] + y + strlen(x, y)) || (start_length[x0] + y0 + strlen(x, y) <= start_length[x] + y + strlen(x, y) && start_length[x0] + y0 + strlen(x, y) >= start_length[x] + y))
            cout << "overwrite" << endl;
        else
        {
            for (int i = 0; i <= strlen(x, y); i++)
            {
                A[start_length[x0] + y0 + i] = A[start_length[x] + y + i];
            }
            check(start_length[x] + y, x);
            check(start_length[x0] + y0, x0);
            check(start_length[x] + y + strlen(x, y), x);
            check(start_length[x0] + y0 + strlen(x, y), x0);
            if (warning == true)
                cout << "wtrue" << endl;
            else
                cout << "true" << endl;
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> length[i]; // 第0~n-1个字符串的长度
    start_length[0] = 0;  //第0个字符串的开头的位置
    for (int i = 1; i < n; i++)
        start_length[i] = start_length[i - 1] + length[i - 1]; //第i个字符串的开头的位置。
    for (int i = 0; i < start_length[n - 1] + length[n - 1]; i++)
        cin >> A[i]; //字符串总长度为start[n-1]+length[n-1]-1（下标最多到这里，再大就越了）
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int opt;
        cin >> opt;
        if (opt == 0)
        {
            int x, y, v, c;
            cin >> x >> y >> v >> c;
			if (v == 0) v = '0';
            memset(x, y, v, c);
        }
        else if (opt == 1)
        {
            int x0, y0, x1, y1;
            cin >> x0 >> y0 >> x1 >> y1;
            strcpy(x0, y0, x1, y1);
        }
        else if (opt == 2)
        {
            int x1, y1;
            cin >> x1 >> y1;
            warning = false;
            int t = strlen(x1, y1);
            if (start_length[x1] + y1 + t > start_length[n - 1] + length[n - 1] - 1)
                cout << "overflow" << endl;
            else if (check(start_length[x1] + y1, x1) == true)
            {
                if (warning == true)
                    cout << "w" << t << endl;
                else
                    cout << t << endl;
            }
            else
                cout << "overflow" << endl;
        }
    }
    return 0;
}
