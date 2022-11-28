#include <cstdio>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;
string platform[10];
string S[101];
int sum, n;
int print(int x, int a, int b)
{
    printf("Move %s from %s to %s.", S[x].c_str(), platform[a].c_str(), platform[b].c_str());
    return 0;
}
int move(int x, int a, int b, int c)
{
    if (x == 1)
    {
        print(x, a, b);
        sum++;
        if (sum != (int)pow(2, n) - 1)
            printf("\n");
    }
    else
    {
        move(x - 1, a, c, b);
        print(x, a, b);
        sum++;
        printf("\n");
        move(x - 1, c, b, a);
    }
    return 0;
}
int main()
{
    scanf("%d\n", &n);
    getline(cin, platform[1]);
    getline(cin, platform[2]);
    getline(cin, platform[3]);
    for (int i = n; i >= 1; i--)
    {
        getline(cin, S[i]);
    }
    move(n, 1, 2, 3);
    return 0;
}
