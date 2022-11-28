#include <bits/stdc++.h>
using namespace std;

template <typename Type>
void read(Type &a) {
    int t;
    while (!isdigit(t = getchar()));
    a = t - '0';
    while ( isdigit(t = getchar())) {
        a *= 10;
        a += t - '0';
    }
}

class MyDeque {
private:
    
    
    deque<long long> values;
    deque<long long> types;
    
    int l_need = 0, r_need = 0;
    int *need_1 = NULL, *need_2 = NULL;
    long long (deque<long long>::*end)() = NULL; 
    void (deque<long long>::*push)(long long) = NULL;
    void (deque<long long>::*pop)() = NULL;

    void my_push(long long val, int type) {
        values.push(val);
        values.push(type);
    }
    void my_pop() {
        values.pop();
        values.pop();
    }

public: 
    long long max_val = 0;    
    void my_add(int pos, int type, int val) { 
        need_1 = pos ? &l_need : &r_need;
        need_2 = pos ? &r_need : &l_need;
        end = pos ? (&deque<long long>::back) : (&deque<long long>::front);
        push = pos ? (&deque<long long>::push_back) : (&deque<long long>::push_front);
        pop = pos ? (&deque<long long>::pop_back) : (&deque<long long>::pop_front);

        switch (type) {
            case pos^0: // pos = 0, ( ; pos = 1, )
                if (*need_1) {
                    *need_1--;
                    if (!type.empty() && types.end() == 2) {
                        val += values.end();
                        my_pop();
                        types.end() = 2;
                        values.end() += val;
                    } 
                    
                } else {
                    *need_2++;
                    my_push(val, type);
                }
                break;

            case pos^1: // pos = 0, ) ; pos = 1, (
                *need_1++;
                my_push(val, type);
                break;
                
            case 2: // sweet
                if (!type.empty() && type.end() == 2) {
                    values.end() += val;
                } else {
                    my_push(val, type);
                }
                break;
        }
        if (!type.empty() && type.end() == 2 && values.end() > max_val) max_val = values.end();
    }
};

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> origin;
    int N, M;
    read(N), read(M);
    origin.resize(N);
    for (int i = 0; i < N; i++)
        read(origin[i]);
    MyDeque deq;
    int pos, type, value;
    for (int i = 0; i < N; i++) {
        read(value);
        deq.my_add(1, origin[i], value);
    }
    cout << deq.max_val << endl;
    while (M--) {
        read(pos), read(type), read(value);
        deq.my_add(pos, type, value);
        cout << deq.max_val << endl; 
    }
    return 0;
}
