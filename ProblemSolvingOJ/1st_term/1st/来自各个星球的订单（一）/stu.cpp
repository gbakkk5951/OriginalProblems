#include <iostream>
using namespace std;
void draw(char y);
int main()
{
    int t;
    cin >> t;
    char a[t];
    int x = 0;
    while (x < t)
    {
        cin >> a[x];
        draw(a[x]);
        x++;
    }
    return 0;
}
char pic[8][10] = {' '};
#include <cstring>
void draw(char y)
{	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			printf("(%d, %d), is %d\n", i, j, (int)pic[i][j]);
		}
	}
	memset(pic, ' ', sizeof(pic));
    for (int i = 0; i < 8; i++)
    {
        for (int j = i; j <= i + 2; j++)
        {
            pic[i][j] = y;
        }
        for (int k = 7 - i; k <= 9 - i; k++)
        {
            pic[i][k] = y;
        }
        for (int l = 0; l < 10; l++)
        {
            cout << pic[i][l];
        }
        cout << endl;
    }
}
