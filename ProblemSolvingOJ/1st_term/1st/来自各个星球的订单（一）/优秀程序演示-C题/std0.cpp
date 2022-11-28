#include <iostream>
#include <iomanip>
#include <cmath>
int main()
{
    using namespace std;
    double i, time, acc;
    double distance;
    cin >> i;
    for (int m = 0; m < i; m++)
    {
        cin >> acc >> time;
        distance = (acc * time * time) * 0.5;
        distance = abs(distance);
        cout << setiosflags(ios::fixed) << setprecision(1) << distance << endl;
    }
    return 0;
}
