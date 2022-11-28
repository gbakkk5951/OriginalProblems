 #include <iostream>
#include <deque>
using namespace std;
const int M = 4 * 1e6 + 5;
char c[M];
int a[M];
deque <int> q;
int main(int argc, const char * argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", c);
    for (int i = 0; i < m; i++){
        if (c[i] == '1') a[i] = 1;
        if (c[i] == '0') a[i] = 0;
    }
    int emptyNum = n;
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < m; i++){
        
        if (emptyNum > 0 && a[i] == 0){
            q.push_back(1);
            emptyNum--;
        }
        else if (a[i] == 0){
            q.push_back(0);
        }
        if (a[i] == 1){
            if (!q.empty()){
                if (q.size() >= 2 && emptyNum == n - 1){
                    if (q.front() == 1)
                        ans += 2;
                    else
                        ans += 4;
                    q.pop_front();
                    q.pop_back();
                    q.push_back(2);
                }
                else if (q.front() == 1){
                    //cout << "b" << endl;
                    ans += 2;
                    emptyNum++;
                    q.pop_front();
                }
                else if (q.front() == 0){
                    //cout << "c" << endl;
                    ans += 4;
                    q.pop_front();
                }
                else{
                    ans += 4;
                    emptyNum++;
                    q.pop_front();
                }
            }
        }
        /*cout << "empty " << emptyNum << endl;
        cout << q.size() << endl;
        cout << endl;*/
    }
    printf("%d", ans);
    return 0;
}


