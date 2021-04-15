#include <iostream>
using namespace std;

int num[100];

void solve(int n, int p) {
	int idx = 0;
	while (n > 0) {
		num[idx % p]++;
		n--;  idx++;
	}
}

void solve_with_comb() {

}

int main() {
	int tc, t, n, p;
	long long ans;
	cin >> tc;
	for (t = 1; t <= tc; ++t) {
		cin >> n >> p;

		/* setup */
		for (int i = 0; i < p; ++i) num[i] = n / p;
		solve(n % p, p);

		ans = 1;
		for (int i = 0; i < p; ++i) ans *= num[i];

		cout << "#" << t << " " << ans << '\n';
	}

	return 0;
}

