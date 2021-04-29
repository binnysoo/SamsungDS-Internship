#include <cstdio>
#define MAX_SZ	31

int N;
int dp[MAX_SZ], sum[MAX_SZ], fac[MAX_SZ];

int get_fac(int n) {
	if (n == 0) return fac[n] = 1;
	return fac[n] = get_fac(n - 1) * n;
}

int main() {
	scanf("%d", &N);

	// N이 홀수인 경우는 다 채우는 것이 불가능하다.
	if (N & 1) printf("0");
	else {
		get_fac(N);
		dp[2] = 3;
		for (int i = 4; i <= N; ++i) {
			for (int j = 2; j < i; ++j) {
				if (i % j == 0) {
					int tmp = 1;
					for (int k = 0; k < i / j; ++k) tmp *= dp[j];
					dp[i] += tmp;
				}
			}

			int type1, type2; // type1 : 2*1    type2 : 1*2
			int newN = N / 2 - 1;
			for (type1 = 0; type1 <= newN / 2; ++type1) {
				type2 = newN - (type1 * 2);
				int tmp = fac[type1 + type2] / (fac[type1] * fac[type2]);
				dp[i] += (tmp * 2);
			}
		}
		dp[0] = sum[0] = 1;
		for (int i = 2; i <= N; i += 2) {
			dp[i] = dp[i - 2] + sum[i - 2] * 2;
			sum[i] = sum[i - 2] + dp[i];
		}
		printf("%d", dp[N]);
	}

	return 0;
}
