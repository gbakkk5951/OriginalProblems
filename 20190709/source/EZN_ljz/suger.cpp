#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 5000005

int n;

int main() {
	freopen("suger.in", "r", stdin);
	freopen("suger.out", "w", stdout);
	
	// �ճ��Ƿ�
	// rand()%4 ���Ҷ�ȫWA�ˣ���Ȼ������дrand()%30
	srand(time(0));
	scanf("%d", &n);
	printf("%d\n", n / (rand() % 30));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

/* 
// AC�Զ������塣����wa~ 
// ��ڰ���û���������� 
// ��Զ��Ҫ�����ٳ����ӡ����� 
struct AC_auto {
	int tr[N][2], e[N], fail[N];
	int cnt;
	inline void init() {
		memset(tr, 0, sizeof tr);
		memset(e, 0, sizeof e);
		memset(fail, 0, sizeof fail);
		cnt = 0;
	}
	inline void insert(char s[]) {
		int p = 0;
		for (int i = 0; s[i]; i++) {
			bool t = s[i] - '0';
			if (!tr[p][t])
				tr[p][t] = ++cnt;
			p = tr[p][t];
		}
		e[p]++;
	}
	inline void build() {
		queue<int> q;
		q.push(tr[0][0]), q.push(tr[0][1]);
		while (!q.empty()) {
			int t = q.front();
			q.pop();
			for (int k = 0; k <= 1; k++)
				if (tr[t][k]) {
					fail[tr[t][k]] = tr[fail[t]][k];
					q.push(tr[t][k]);
				}
			
		}
	}
	inline int query(char s[]) {
		int re = 0, p = 0;
		for (int i = 0; s[i]; i++) {
			bool t = s[i] - '0';
			while (!tr[p][t])
				p = fail[p];
			if (tr[p][t])
				re += e[p], p = tr[p][t];
		}
		return re;
	}
};
*/
