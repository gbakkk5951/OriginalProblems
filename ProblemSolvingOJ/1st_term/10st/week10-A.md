
### 1. 考察知识：模拟，字符串基础

### 2. 优秀代码
**一**
作者：张浩宇
助教自己写的
这题本来是要在第五周用来衔接《异星工厂：流水线》的，因为很多同学并不了解字符串在内存中的存储方式
所以让同学们手动实现memset，strlen，strcpy来更深刻理解指针、内存

```c++
#include <bits/stdc++.h>
using namespace std;
namespace Archaeology {
const int maxn = 1e3 + 5;
char memory[maxn];//使用char类型，使得可以在判定合法后能够直接调用库函数
int s[maxn];// i号数组的范围为 s[i] ~ s[i + 1] - 1
int n, m;
bool warning;
bool check(int p, int x) {
	if (p < 0 || p >= s[n]) {
		return false;
	}
	if (s[x] > p || p >= s[x + 1]) {
		warning = true;
	}
	return true;
}
int memset(int x0, int y0, int v, int c) {
	int p = s[x0] + y0;
	for(int i = 0; i < c; ++i) {
		if (!check(p + i, x0)) {
			return 0;
		}
	}
	::memset(memory + p, v, c); // ::表示最外层的命名空间
	return 1;
}
int strcpy(int x0, int y0, int x1, int y1) {
	int p0 = s[x0] + y0, p1 = s[x1] + y1;
	int sl = p0, dl = p1, sr, dr; //dl表示destination left, dr 表示destination right; sl, sr表示source left/right
	for (sr = sl, dr = dl; ; ++sr, ++dr) { //条件为空表示无条件执行
		if (check(sr, x0) && check(dr, x1)) {
			if (memory[sr] == 0) break;
		} else {
			return -1;
		}
	}
	if (dr < sl || sr < dl) {
		::strcpy(memory + dl, memory + sl);//注意顺序
		return 1;
	}
	return 0;
}
int strlen(int x0, int y0) {
	int p = s[x0] + y0, len = 0;
	while (1) {
		if (check(p, x0)) {
			if (memory[p] == 0) {
				break;
			}
			++len;
			++p;
		} else {
			return -1;
		}
	}
	assert(len == ::strlen(&memory[s[x0] + y0]));// 检测是否正确，可以删掉
	return len;
}
ostream& coutw() {//在输出前自动加上w，ostream表示输出流，cout是输出流的一种，返回值是cout
	return cout << (warning ? "w" : "");
}

}
int main() {
	using namespace Archaeology;
	ios::sync_with_stdio(false);
	cin >> n;
	
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		s[i] += s[i - 1];
		assert(s[i] <= 1000);//用来检测数据合法性，可以删掉
	}
	if (s[n] > 1000) while(1);//用来检测数据合法性，可以删掉
	for (int i = 0, t; i < s[n]; ++i) {
		cin >> t; //因为memory是char类型，所以可以用int类型的t作为中介
		memory[i] = t;
	}
	cin >> m;
	for (int i = 1, op, a, b, c, d; i <= m; ++i) {
		warning = false;
		cin >> op;
		switch (op) {
			case 0: {
				cin >> a >> b >> c >> d;
				if (memset(a, b, c, d)) {
					coutw() << "true" << endl; //coutw()的返回值是cout
				} else {
					cout << "overflow" << endl;
				}
				break;
			}
			case 1: {
				cin >> a >> b >> c >> d;
				int ret = strcpy(a, b, c, d);
				if (ret == 1) {
					coutw() << "true" << endl;
				} else
				if (ret == 0) {
					cout << "overwrite" << endl;
				} else { //ret == -1 
					cout << "overflow" << endl;
				}
				break;
			}
			case 2: {
				cin >> a >> b;
				int ret = strlen(a, b);
				if (ret == -1) {
					cout << "overflow" << endl;
				} else {
					coutw() << ret << endl;
				}
				break;
			}
		}
	}
	return 0;
}


```


**二**
作者：张天昀
[张天昀的实况解说](https://www.bilibili.com/video/BV1hb4y1B7Tm)

```C++
#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>

using std::vector;

struct Result {
  bool illegal;
  bool overwrite;
  int value;
};

class Solution {
 private:
  int n;
  vector<int> m;
  vector<int> p;  // prefix sum
  vector<int> s;

 private:
  int get_pos(int x, int y) { return p[x] + y; }
  bool is_illegal(int pos) { return pos < 0 || pos >= p[n]; }
  bool is_overwrite(int x, int pos) { return pos < p[x] || pos >= p[x + 1]; }

 private:
  Result memset(int x, int y, int v, int c) {
    bool overwrite = false;
    int length = 0;
    int pos = get_pos(x, y);
    if (c > 0 && (is_illegal(pos) || is_illegal(pos + c - 1))) {
      return {true, false, 0};
    }
    for (int i = 0; i < c; ++i) {
      overwrite |= is_overwrite(x, pos + i);
      s[pos + i] = v;
    }
    return {false, overwrite, 0};
  }
  Result strcpy(int x0, int y0, int x1, int y1) {
    Result result = strlen(x0, y0);
    if (result.illegal) {
      return {true, false, 0};
    }
    // pos0        pos0+len
    // ==============
    //          ===============
    //      pos1              pos1+len
    bool overwrite = result.overwrite;
    int length = result.value;
    int pos0 = get_pos(x0, y0);
    int pos1 = get_pos(x1, y1);
    if (is_illegal(pos1) || is_illegal(pos1 + length)) {
      return {true, false, 0};
    }
    overwrite |= is_overwrite(x0, pos0) || is_overwrite(x0, pos0 + length) ||
                 is_overwrite(x1, pos1) || is_overwrite(x1, pos1 + length);
    if ((pos0 < pos1 && pos0 + length >= pos1) ||
        (pos0 >= pos1 && pos1 + length >= pos0)) {
      return {false, overwrite, -1};
    }
    for (int i = 0; i <= length; ++i) {
      s[pos1 + i] = s[pos0 + i];
    }
    return {false, overwrite, 0};
  }
  Result strlen(int x, int y) {
    bool overwrite = false;
    int length = 0;
    int pos = get_pos(x, y);
    while (true) {
      if (is_illegal(pos + length)) {
        return {true, false, 0};
      }
      overwrite |= is_overwrite(x, pos + length);
      if (s[pos + length] == 0) {
        break;
      }
      length++;
    }
    return {false, overwrite, length};
  }

 public:
  void init() {
    scanf("%d", &n);
    m.resize(n, 0);
    p.resize(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &m[i]);
      p[i + 1] = p[i] + m[i];
    }
    s.resize(p[n], 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m[i]; ++j) {
        scanf("%d", &s[get_pos(i, j)]);
      }
    }
  }
  void work() {
    int k = 0;
    scanf("%d", &k);
    while (k--) {
      int op = 0;
      int args[4] = {};
      scanf("%d", &op);
      switch (op) {
        case 0: {
          for (int i = 0; i < 4; ++i) {
            scanf("%d", &args[i]);
          }
          Result res = memset(args[0], args[1], args[2], args[3]);
          if (res.illegal) {
            printf("overflow\n");
          } else {
            printf("%strue\n", res.overwrite ? "w" : "");
          }
          break;
        }
        case 1: {
          for (int i = 0; i < 4; ++i) {
            scanf("%d", &args[i]);
          }
          Result res = strcpy(args[0], args[1], args[2], args[3]);
          if (res.illegal) {
            printf("overflow\n");
          } else if (res.value < 0) {
            printf("overwrite\n");
          } else {
            printf("%strue\n", res.overwrite ? "w" : "");
          }
          break;
        }
        case 2: {
          for (int i = 0; i < 2; ++i) {
            scanf("%d", &args[i]);
          }
          Result res = strlen(args[0], args[1]);
          if (res.illegal) {
            printf("overflow\n");
          } else {
            printf("%s%d\n", res.overwrite ? "w" : "", res.value);
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
};

int main() {
  Solution s;
  s.init();
  s.work();
  return 0;
}
```
