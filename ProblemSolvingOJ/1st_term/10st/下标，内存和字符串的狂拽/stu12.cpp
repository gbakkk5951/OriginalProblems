#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

struct Name {
    bool illegal;
    bool overwrite;
    int value;
};

class Word {
    private:
      int n;
      vector<int> m;
      vector<int> p;
      vector<int> s;

    private:
      int getpp(int xx, int yy){
          return p[xx] + yy;
      }
      bool qillegal(int pp){
          return pp < 0 || pp >= p[n];
      }
      bool qoverwrite(int xx, int pp){
          return pp < p[xx] || pp >= p[xx + 1];
      }

    private:
      Name memset(int X, int Y, int V, int C){
          bool overwrite = false;
          int length = 0;
          int pp = getpp(X, Y);
          if (C > 0 && (qillegal(pp) || qillegal(pp + C - 1))){
              return {true, false, 0};
          }
          if (C == 0){
              return {false,false,0};
          }
          for (int i = 0; i < C; ++ i){
              overwrite |= qoverwrite(X, pp + i);
              s[pp + i] = V;
          }
          return {false, overwrite, 0};
      }
      Name strcpy(int X0, int Y0, int X1, int Y1){
          Name name = strlen(X0, Y0);
          int length = name.value;
          int pp0 = getpp(X0, Y0);
          int pp1 = getpp(X1, Y1); 
          if (name.illegal || qillegal(pp0 + length) || qillegal(pp0) || qillegal(pp1) || qillegal(pp1 + length)){
              return {true, false, 0};
          }
          bool overwrite = qoverwrite(X0, pp0 + length) || qoverwrite(X1, pp1 + length) || qoverwrite(X0, pp0) || qoverwrite(X1, pp1);
          if((pp0 < pp1 && pp0 + length >= pp1) || (pp0 >= pp1 && pp1 + length >= pp0)){
              return {false, overwrite, -1};
          }
          for(int i = 0; i <= length; i ++){
              s[pp1 + i] = s[pp0 + i];
          }
          return {false, overwrite, 0};
      }
      Name strlen(int Xx, int Yy){
          bool overwrite = false;
          int length = 0;
          int pp = getpp(Xx, Yy);
          if (qillegal(pp)){
              return {true, false, 0};
          }
          for (; (!qillegal(pp + length)) && (s[pp +length] != 0); ++ length){
              overwrite |= qoverwrite(Xx, pp + length);
          }
          if (qillegal(pp + length)){
              return {true, false, 0};
          }
          overwrite |= qoverwrite(Xx, pp + length);
          return {false, overwrite, length};
      }

    public:
      void in(){
          scanf("%d", &n);
          m.resize(n, 0);
          p.resize(n + 1, 0);
          p[0] = 0;
          for (int i = 0; i <= n - 1; i ++){
              scanf("%d", &m[i]);
              p[i + 1] = p[i] + m[i];
          }
          s.resize(p[n], 0);
          for (int i = 0; i < n; i ++){
              for (int j = 0; j < m[i]; j++){
                  scanf("%d", &s[getpp(i, j)]);
              }
          }
      }
      void work(){
          int k;
          scanf("%d", &k);
          for (int u = 1; u <= k; u ++){
              int op;
              scanf("%d", &op);
              if(op == 0){
                  int x, y, v, c;
                  scanf("%d%d%d%d", &x, &y, &v, &c);
                  if ((y > -1000) && (y < 1000)){
                  Name last = memset(x, y, v, c);
                  if(last.illegal){
                      printf("overflow\n");
                  }
                  else{
                      printf("%strue\n", last.overwrite ? "w" : "");
                  }
                  }
                  else printf("overflow\n");;
              }
              else if(op == 1){
                  int x0, y0, x1, y1;
                  scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
                  if ((y0 > -1000) && (y0 < 1000) && (y1 > -1000) && (y1 < 1000)){
                  Name last = strcpy(x0, y0, x1, y1);
                  if(last.illegal){
                      printf("overflow\n");
                  }
                  else if (last.value < 0){
                      printf("overwrite\n");
                  }
                  else{
                      printf("%strue\n", last.overwrite ? "w" : "");
                  }
                  }
                  else printf("overflow\n");
              }
              else if(op == 2){
                  int x, y;
                  scanf("%d%d", &x, &y);
                  if ((y > -1000) && (y < 1000)){
                  Name last = strlen(x, y);
                  if(last.illegal){
                      printf("overflow\n");
                  }
                  else{
                      printf("%s%d\n", last.overwrite ? "w" : "", last.value);
                  }
                  }
                  else printf("overflow\n");
              }
          }
      }
};

int main(){
    Word s;
    s.in();
    s.work();
    return 0;
}
