#include <cstdio>
#include <cctype>
template <typename Type>
    void read(Type &a) {
        char t;
        while (!isdigit(t = getchar()));
        a = t - '0';
        while ( isdigit(t = getchar())) {
            a *= 10;
            a += t - '0';
        }
    }
int main() {
    int a;
    read(a);
    printf("%d", a);
}
