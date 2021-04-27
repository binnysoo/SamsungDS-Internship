#include <iostream>
#define MAX_SZ	12
using namespace std;

int N;
int arr[MAX_SZ];
int op[4], cnt[4];
int max_val = -1000000000, min_val = 1000000000;

void dfs(int size, int total, int sum, int sub, int mul, int div) {
	if (size == N) {
		if (max_val < total) max_val = total;
		if (min_val > total) min_val = total;

		return;
	}

	if (sum > 0) dfs(size + 1, total + arr[size], sum - 1, sub, mul, div);
	if (sub > 0) dfs(size + 1, total - arr[size], sum, sub - 1, mul, div);
	if (mul > 0) dfs(size + 1, total * arr[size], sum, sub, mul - 1, div);
	if (div > 0) dfs(size + 1, total / arr[size], sum, sub, mul, div - 1);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}
	for (int i = 0; i < 4; ++i) {
		cin >> op[i];
	}
	dfs(1, arr[0], op[0], op[1], op[2], op[3]);

	cout << max_val << '\n' << min_val;

	return 0;
}