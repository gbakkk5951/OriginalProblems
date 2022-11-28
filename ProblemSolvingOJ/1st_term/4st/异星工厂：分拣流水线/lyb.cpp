#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;
int main() {
    vector<char> string_line;
    long long integer_A(0), number(-1);
    int count(0);
    long double float_B(0);
    vector<char> lower_C, upper_D;
    char input;
    bool isnumber(false), isfloat(false);
    while ((input = getchar()) != EOF)
        string_line.push_back(input);
    string_line.push_back('\0');
    for (char c : string_line) {
        if ('a' <= c && c <= 'z') {
            isnumber = false;
            upper_D.push_back(c - 32);
        }
        else if ('A' <= c && c <= 'Z') {
            isnumber = false;
            lower_C.push_back(c + 32);
        }
        else if ('0' <= c && c <= '9') {
            double d = c - '0';
            isnumber = true;
            if (number < 0) number = 0;
            if (isfloat == true)
                count += 1;
            number *= 10;
            number += d;
        }
        else if (c == '.') {
            isnumber = true;
            isfloat = true;
            if (number < 0) number = 0;
        }
        else if (c == '\0') {
            isnumber = false;
        }
        if (number != -1) {
            if (isnumber == false && isfloat == false) {
                integer_A += number;
                number = -1;
            }
            if (isnumber == false && isfloat == true) {
                isfloat = false;
                number *= pow(10,(2 - count));
                float_B += number;
                number = -1;
                count = 0;
            }   
        }
    }
    float_B /= 100.0; 
    printf("%lld\n", integer_A);
    printf("%.2Lf \n", float_B);
    for (char c : lower_C) printf("%c", c);
    printf("\n");
    for (char c : upper_D) printf("%c", c);
    return 0;
}
