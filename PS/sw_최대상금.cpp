#include <iostream>
#define MAX_LEN		11
using namespace std;

char num[MAX_LEN];
int len;

typedef pair<int, int> pii;
pii candidates[MAX_LEN * MAX_LEN];
pii to_swap[MAX_LEN];

int max2(int a, int b) {
	return a > b ? a : b;
}

int get_len(char *str) {
	int idx = 0;
	char c = str[idx++];
	while (c != '\0') {
		c = str[idx++];
	}
	return idx - 1;
}

int to_int(char *str) {
	int result = 0;
	char c;
	for (int i = 0; i<len; ++i)  {
		c = str[i];
		result = (result * 10) + (c - '0');
	} 
	return result;
}

char * to_str(int n) {
	char *str = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = len - 1; i >= 0; --i) {
		str[i] = (char)(n % 10 + '0');
		n /= 10;
	}
	str[len] = '\0';
	return str;
}

void copy_str(char *src, char *dest) {
	for (int i = 0; i < len; ++i) {
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

/* Swap the selected indices and get result */
int swapped_result(int n) {
	int i, x, y;
	char tmp[MAX_LEN];

	copy_str(num, tmp);
	for (i = 0; i < n; ++i) {
		x = to_swap[i].first; y = to_swap[i].second;
		swap(tmp[x], tmp[y]);
	}
	return to_int(tmp);
}

/* Combination with repetition */
int solve(int n, int r, int r2, int max_val) {
	if (r == 0) {
		// check value
		return max2(swapped_result(r2), max_val);
	}
	else if (n < 1) return -1; // invalid case
	else {
		to_swap[r - 1] = candidates[n - 1];
		int ret1 = solve(n, r - 1, r2, max_val); 
		int ret2 = solve(n - 1, r, r2, max_val); 

		max_val = max2(ret1, ret2);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int tc, t, n, i, j;
	cin >> tc;
	for (t = 1; t <= tc; ++t) {
		cin >> num >> n;
		len = get_len(num);

		// Fill candidates
		int idx = 0;
		for (i = 0; i < len; ++i) {
			for (j = i + 1; j < len; ++j) {
				candidates[idx++] = make_pair(i, j);
			}
		}
		// Select n pairs from candidates and swap
		cout << "#" << t << " " << solve(idx, n, n, -1) << '\n';
	}

	return 0;
}