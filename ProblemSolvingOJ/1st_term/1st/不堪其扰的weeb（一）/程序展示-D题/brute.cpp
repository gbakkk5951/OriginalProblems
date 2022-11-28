#include <iostream>
using namespace std;

int main()
{
    char c;
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++)
    {
        cin >> c;
        cout << c << c << c << "    " << c << c << c << endl;
        cout << " " << c << c << c << "  " << c << c << c << " " << endl;
        cout << "  " << c << c << c << c << c << c << "  " << endl;
        cout << "   " << c << c << c << c << "   " << endl;
        cout << "   " << c << c << c << c << "   " << endl;
        cout << "  " << c << c << c << c << c << c << "  " << endl;
        cout << " " << c << c << c << "  " << c << c << c << " " << endl;
        cout << c << c << c << "    " << c << c << c << endl;
    }

    return 0;
}
