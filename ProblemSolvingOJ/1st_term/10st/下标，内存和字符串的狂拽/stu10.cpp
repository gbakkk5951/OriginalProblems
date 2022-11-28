#include <iostream>
using namespace std;
const int MaxN = 1000 + 5;
int n, k, op;
//
int lenTrueArray;
int numArray[MaxN];
int TrueArray[MaxN];
int sum[MaxN];
//
int Sum(int x)
{
    sum[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + numArray[i - 1];
    }
    return sum[x];
}
//
bool warning;            //FIXME:warning初始化了吗？
bool check(int p, int x) //y < 0 时你warning了吗？提示的3种情况都考虑了吗？
{
    if (p < 0 || p >= sum[n])
    { //非法访问
        return false;
    }
    if (sum[x] > p || p >= sum[x + 1])
    { //合法的越界访问
        warning = true;
    }
    return true; //合法，包括越界和不越界
}
//
//
void MyMemset(int x, int y, int v, int c) //FIXME:warning初始化了吗？
{
    int start = Sum(x) + y;
    //WarningPart
    warning = false;

    bool StartCheck1 = check(start, x); //FIXME:warning真的被改变了吗？
    bool StartCheck2 = check(start + c - 1, x);
    if (c == 0)
    {
        goto Flag;
    }
    if (StartCheck1 == false || StartCheck2 == false)
    {
        cout << "overflow" << endl;
        return;
    }

    if (warning == true)
        cout << "w";
//
Flag:
    for (int i = 0; i < c; i++)
        TrueArray[start + i] = v;
    cout << "true" << endl;
    //testline
    /*cout << "TrueArray is " << endl;
    for (int i = 0; i < lenTrueArray; i++)
    {
        cout << TrueArray[i];
    }*/
    return;
}
void Mystrcpy(int x0, int y0, int x1, int y1) //FIXME:warning初始化了吗？
{
    int startSource = Sum(x0) + y0;
    int startDestination = Sum(x1) + y1;
    //WarningPart
    //
    warning = false;
    bool StartCheck1 = check(startSource, x0);
    bool StartCheck2 = check(startDestination, x1);
    if (StartCheck1 == false || StartCheck2 == false)
    {
        cout << "overflow" << endl;
        return;
    }
    int lenSource = 1;
    for (int i = 0; TrueArray[startSource + i] != 0; i++)
    {
        lenSource++;
        bool CheckChoose = check(startSource + i + 1, x0);
        if (CheckChoose == false)
        {
            cout << "overflow" << endl;
            return;
        }
    }
    bool StartCheck3 = check(startDestination + lenSource - 1, x1);
    if (StartCheck3 == false)
    {
        cout << "overflow" << endl;
        return;
    }
    //交集判断
    if (startSource <= startDestination && startSource + lenSource - 1 >= startDestination)
    {
        cout << "overwrite" << endl;
        return;
    }
    if (startDestination < startSource && startDestination + lenSource - 1 >= startSource)
    {
        cout << "overwrite" << endl;
        return;
    }
    //开始复制
    if (warning == true)
        cout << "w";
    for (int i = 0; i < lenSource; i++)
    {
        TrueArray[startDestination + i] = TrueArray[startSource + i];
    }
    cout << "true" << endl;
    //testline
    /*cout << "TrueArray is " << endl;
    for (int i = 0; i < lenTrueArray; i++)
    {
        cout << TrueArray[i];
    }
    cout << endl;*/
    return;
}
void Mystrlen(int x, int y, int lenTrueArray) //FIXME:warning初始化了吗？
{
    int startCount = Sum(x) + y;
    ///WarningPart
    warning = false;
	if (!check(startCount, x)) {
		cout << "overflow" << endl;
		return;
	}
    for (int i = 0; TrueArray[startCount + i] != 0; i++)
    {
        bool StartCheck1 = check(startCount + i, x);
        if (StartCheck1 == false)
        {
            cout << "overflow" << endl;
            return;
        }
        bool StartCheck2 = check(startCount + i + 1, x);
        if (StartCheck2 == false)
        {
            cout << "overflow" << endl;
            return;
        }
    }
    if (warning == true)
        cout << "w";
    /*for (int i = 0; startCount + i <= lenTrueArray; i++) //FIXME:is it correct?
    {
        //
        if (startCount + i < 0 || startCount + i >= sum[n])
        { //非法访问
            cout << "overflow" << endl;
            return;
        }
        //
        if (TrueArray[startCount + i] == 0)
        {
            break;
        }

        bool StartCheck = check(startCount, x + i);
        if (StartCheck == false)
        {
            cout << "overflow" << endl;
            return;
        }
    }
    if (warning == true)
        cout << "w";*/
    //
    int strlength = 0;
    for (int i = 0; TrueArray[startCount + i] != 0; i++)
    {
        //testline
        //cout << "Now checking:" << TrueArray[startCount + i] << endl;
        strlength++;
    }
    cout << strlength << endl;
    return;
}
//
//
int main()
{
    int x, y, v, c, x0, y0, x1, y1;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> numArray[i];
    for (int i = 0; i < n; i++)
    {
        lenTrueArray = lenTrueArray + numArray[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < numArray[i]; j++)
            cin >> TrueArray[Sum(i) + j];
    //testline
    /*cout << "TrueArray is " << endl;
    for (int i = 0; i < lenTrueArray; i++)
    {
        cout << TrueArray[i];
    }*/
    //
    cin >> k;
    while (k--)
    {
        cin >> op;
        switch (op)
        {
        case 0:
            cin >> x >> y >> v >> c;
            MyMemset(x, y, v, c);
            break;
        case 1:
            cin >> x0 >> y0 >> x1 >> y1;
            Mystrcpy(x0, y0, x1, y1);
            break;
        case 2:
            cin >> x >> y;
            Mystrlen(x, y, lenTrueArray);
            break;

        default:
            break;
        }
    }
    return 0;
}
