#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include <iomanip>
using namespace std;
const int N = 1000000 + 5;
char s[N];
int A;
double B;
string C, D;
int main()
{
    scanf("%s", s);
    int len = strlen(s);
    bool flag = 0;
    int l = -1, dightLen = 0;
    double tep = 0;

    for (int i = 0; i <= len; i++)
    {
        if (s[i] == '.' || isdigit(s[i]))
        {
          l = (l == -1) ? i : l;
          dightLen = dightLen + 1;
          if (s[i] == '.') flag = true;
        }
        else {
          if (dightLen) {
            char c = s[l + dightLen];
            s[l + dightLen] = 0;
            sscanf(s + l, "%lf", &tep);
            if (!flag) A += tep;
            else B += tep;
            s[l + dightLen] = c;
            dightLen = 0;
            l = -1;
            flag = false;
          }

          if (islower(s[i])) D += toupper(s[i]);
          else if (isupper(s[i])) C += tolower(s[i]);
        }
    }
    cout << A << endl << setiosflags(ios::fixed) << setprecision(2) << B << endl << C << endl << D;
    return 0;
}
