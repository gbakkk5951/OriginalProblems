int functionA(int index) {
	int ans = index;
	for (int i = 2; i <= index; ++i) {
		(ans += functionA(index / i)) %= 998244353;
	}
	return ans;
}
