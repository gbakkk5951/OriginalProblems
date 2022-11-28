#include <iostream>
#include <queue>
using namespace std;
const int M = 4 * 1e6 + 5;
char c[M];
int a[M];
queue <int> q;
int main(int argc, const char * argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    scanf("%s", c);
    for (int i = 0; i < m; i++){
        if (c[i] == '1') a[i] = 1;
        if (c[i] == '0') a[i] = 0;
    }
    int emptyNum = n;
    int ans = 0;
    for (int i = 0; i < m; i++){
        
        if (emptyNum > 0 && a[i] == 0){
            q.push(1);
            emptyNum--;
        }
        else if (a[i] == 0){
            q.push(0);
        }
        if (a[i] == 1){
            if (!q.empty()){
                if (q.size() >= 2 && emptyNum == n - 1){
                    //cout << "a" << endl;
                    ans += 2;
                    q.pop();
                }
                else if (q.front()){
                    //cout << "b" << endl;
                    ans += 2;
                    emptyNum++;
                    q.pop();
                }
                else{
                    //cout << "c" << endl;
                    ans += 4;
                    if (q.size() == 1 && emptyNum == n - 1){
                        emptyNum++;
                    }
                    q.pop();
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


