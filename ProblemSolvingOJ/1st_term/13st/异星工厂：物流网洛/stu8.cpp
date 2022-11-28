#include <iostream>
using namespace std;
bool temp1 = 0, temp2 = 0;
int Inf[50], Sup[50];
int count1 = 0, count2 = 0;
bool Chart[50][50];
bool Rela[50][50];
int main()
{
    int T, n;
    cin >> T;
    while (T--)
    {
        cin >> n;
        bool right = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> Chart[i][j];
                if (i == j && Chart[i][j] != 1)
                    right = 0;
            }
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Rela[i][j] = Chart[i][j];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (Chart[i][j])
                    for (int k = 0; k < n; k++)
                        if (Chart[j][k])
                            Rela[i][k] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (Chart[i][j] != Rela[i][j])
                    right = 0;
        if (!right)
        {
            cout << "N" << endl;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    count1 = 0, count2 = 0;
                    temp1 = 0, temp2 = 0;
                    for (int k = 0; k < n; k++)
                    {
                        if (Chart[k][i] && Chart[k][j])
                        {
                            Inf[count1++] = k;
                            //cout << "Inf" << i + 1 << " " << j + 1 << " " << k + 1 << endl;
                        }
                        if (Chart[i][k] && Chart[j][k])
                        {
                            Sup[count2++] = k;
                            //cout << "Sup" << i + 1 << " " << j + 1 << " " << k + 1 << endl;
                        }
                    }
                    for (int k = 0; k < count1; k++)
                    {
                        temp1 = 1;
                        for (int l = 0; l < count1; l++)
                        {
                            if (!Chart[Inf[l]][Inf[k]])
                                temp1 = 0;
                        }
                        if (temp1)
                            break;
                    }
                    for (int k = 0; k < count1; k++)
                    {
                        temp2 = 1;
                        for (int l = 0; l < count1; l++)
                        {
                            if (!Chart[Sup[k]][Sup[l]])
                                temp2 = 0;
                        }
                        if (temp2)
                            break;
                    }
                    if (!temp1 || !temp2)
                        right = 0;
                }
            }
            if (right)
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
}
