#include <bits/stdc++.h>
using namespace std;
long long read() {
    long long a;
	int f = 0, t;
	while (!isdigit(t = getchar())) {
		f |= t == '-';
	} 
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10; a += t - '0';
	}
	a = f ? -a : a;
	return a;
}
long long a[1000005];
long long absq[1000005];
long long big[1000005];
int n, k;
int main()
{

    n = read(); k = read();

    int mid = 0;
    long long midelement = 0;
    if (n % 2 == 0)
    {
        for (int i = 0; i < n; i++)
            a[i] = 2 * read();
        mid = n / 2;
        nth_element(a, a + mid - 1, a + n);
        long long temp = a[mid - 1];
        nth_element(a, a + (mid), a + n);
        midelement = (temp + a[mid]) / 2;
    }
    else
    {
        for (int i = 0; i < n; i++)
            a[i] = read();
        mid = n / 2 + 1;
        nth_element(a, a + mid - 1, a + n);
        midelement = a[mid - 1];
    }
    for (int i = 0; i < n; i++)
    {
        if (midelement - a[i] <= 0)
        {
            absq[i] = -midelement + a[i];
            big[i] = 1;
        }
        else
            absq[i] = midelement - a[i], big[i] = 0;
    }
    nth_element(absq, absq + k - 1, absq + n);
    long long smallone = absq[k - 1];
    // cout << "smallone" << smallone << endl;
    long long ans = 0;
    int number = k;
    for (int i = 0; i < n; i++)
    {
        long long temp = a[i] - midelement;
        if (temp < 0)
            temp = -temp;
        if (temp < smallone)
        {
            ans += a[i];
            number--;
        }
        else if (temp == smallone)
        {
            if (big[i] == 1)
                ans += a[i], number--;
        }
        if (number == 0)
            break;
    }
    while (number > 0)
    {
        if (n % 2 == 0 && (midelement - smallone) % 2) {
            while(1);
        }
        ans += midelement - smallone;
        number--;
    }
    if (n % 2 == 0)
        ans = ans / 2;
    cout << ans;
}
