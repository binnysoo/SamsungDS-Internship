#include <cstdio>
#define MAX_NUM	1000005
#define MOD		1000

int N, a, b, d;
int birth[MAX_NUM], dp[MAX_NUM];

// birth[i]: i번째 날 태어난 짚신벌레 수
// birth[n] = birth[i - a] + birth[i - (a + 1)] + ... birth[i - (b - 1)] 
// death[i]: i번째 날 죽은 짚신벌레 수
// death[n] = birth[n - d]
// dp[i]: i번째 날 짚신벌레 수
// a번쨰 날에 성체, b - 1번째 날까지 개체 생성, d번째 날에 사망
// dp[n] = dp[n - 1] + birth[n] - death[n]

int main() {
	scanf("%d %d %d %d", &a, &b, &d, &N);

	/* init */
	for (int i = 0; i < a; ++i) {
		dp[i] = 1;
	}
	birth[0] = 1; birth[a] = 1;
	dp[a] = dp[a - 1] + birth[a];

	/* fill */
	for (int i = a + 1; i <= N; ++i) {
		if (i >= b) {
			birth[i] = (birth[i - 1] - birth[i - b] + birth[i - a]) % MOD;
			if (birth[i] < 0) birth[i] += MOD;
		}
		else {
			birth[i] = (birth[i - 1] + birth[i - a]) % MOD;
		}

		if (i >= d) {
			dp[i] = (dp[i - 1] + birth[i] - birth[i - d]) % MOD;
			if (dp[i] < 0) dp[i] += MOD;
		}
		else 
			dp[i] = (dp[i - 1] + birth[i]) % MOD;
	}

	printf("%d", dp[N] % 1000);


	return 0;
}