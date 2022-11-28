#include <bits/stdc++.h>
template <typename type>
void read(type &a) {
	int t, f = 0;
	while (!isdigit(t = getchar())) {
		f |= t == '-';
	}
	a = t - '0';
	while ( isdigit(t = getchar())) {
		a *= 10;
		a += t - '0';
	}
	a = f ? -a : a;
}
template <typename type>
void write(type a) {
	char out[35];
	int index = 35;

	out[--index] = 0;
	out[--index] = '\n';
	if (a < 0) {
		putchar('-');
		a = -a;
	}	
	if (a) {
		do {
			out[--index] = a % 10 + '0';
		} while(a /= 10);
	} else {
		out[--index] = '0';
	}
	do {
		putchar(out[index]);
	} while(out[++index]);
}
int n;
const int maxn = 1e6 + 200;
int arr[maxn];
int end[maxn];
typedef std::pair<int, int> pii;
pii heap[128];
int head[maxn];
int hn;
inline int lc(const int &a) {
	return a << 1;
}
inline int rc(const int &a) {
	return a << 1 | 1;
}
inline int p(const int &a) {
	return a >> 1;
}
std::priority_queue<pii> h; 
void push(int bel) {
	if (head[bel] > end[bel]) return;
	
/*	
	heap[++hn] = (pii) {arr[head[bel]], bel};
	int nd= hn;
	while(nd > 1 && heap[p(nd)].first > heap[nd].first) {
		swap(heap[p(nd)], heap[nd]);
		nd = p(nd);
	}
*/	 
	
	h.push((pii) {-arr[head[bel]], bel});
	
	++head[bel];
}
int pop() {
	
	/*
	int bel = heap[1].second;
	int ret = heap[1].first;
	heap[1] = heap[hn--];
	int nd = 1;
	int cho = nd;
	while (1) {
		if (lc(nd) <= hn && heap[lc(nd)].first < heap[cho].first) {
			cho = lc(nd);
		}
		if (rc(nd) <= hn && heap[rc(nd)].first < heap[cho].first) {
			cho = rc(nd);
		}
		if (cho != nd) {
			swap(heap[nd], heap[cho]);
			nd = cho;
		} else {
			break;
		}
	}
	*/
	
	
	int bel = h.top().second;
	int ret = -h.top().first;
	h.pop();
	
	push(bel);
	return ret;
}
int main() {
	int m;
	read(n); read(m);
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		read(s);
		head[i] = end[i - 1] + 1;
		end[i] = end[i - 1] + s;
		for (int j = head[i]; j <= end[i]; ++j) {
			read(arr[j]);
		}
		int flag = arr[head[i]] > arr[end[i]];
		if (flag) for (int x = head[i], j = end[i]; x < j; ++x, --j) {
			std::swap(arr[x], arr[j]);
		}
		push(i);
	}
	for (int i = 1; i <= m; ++i) {
		write(pop());
	}
	return 0;
}
