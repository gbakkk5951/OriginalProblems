#include <iostream>
#include <cstdio>
using namespace std;

char str[1000005];
int sum[1000005];
int main()
{
        freopen("hss.in", "r", stdin);
        freopen("hss.out", "w", stdout);

    int n, m, cnt0 = 0 /*层数 */, cnt1 = 0 /*正负 */, cnt2 = 0 /*答案 */, cnt3 = 0, cnt4 = 0, cnt5 = 0;
    scanf("%d%d%s", &n, &m, &str);

    for (int i = 0; i < n; ++i)
    {
        switch (str[i])
        {
            case 's':
            {
                ++cnt0;
                ++cnt1;
                break;
            }
            case 'h':
            {
                if (cnt0 != 0)
                {
                    cnt2 += sum[cnt0];
                    --cnt0;
                    cnt2 += 2;
                }
                --cnt1;
                break;
            }
            case 'S':
            {
                ++sum[cnt0];
                break;
            }
        }
    }
    
    cout << cnt2 << '\n';
    
    while (m--)
    {
        int p;
        char x;
        cin >> p >> x;
        switch (x)
        {
            case 's':
            {
                if (p == 1)
                {
                    if (cnt1 < 0)
                    {
                        cnt2 += 2;
                        ++cnt1;
                    }
                    else
                    {
                    	if(cnt4 > 0)
                    	{
                    		--cnt4;
                    		cnt2 += 2;
						}
						else
						{
							++cnt3;
						}
					}
                }
                else
                {
                    ++cnt3;
                }
                break;
            }
            case 'h':
            {
                if (p == 1)
                {
                    ++cnt4;
                }
                else
                {
                    if(cnt1 > 0)
                    {
                        cnt2 += 2;
                        --cnt1;
                    }
                    else
                    {
                    	if (cnt3 > 0)
                    	{
                    		--cnt3;
                    		cnt2 += 2;
						}
						else
						{
							++cnt4;
						}
					}
                }
                break;
            }
            case 'S':
            {
                if (p == 1)
                {
                	
                }
                else
                {
                	
                }
                break;
            }
        }
        cout << cnt2 << '\n';
    }
    return 0;
}