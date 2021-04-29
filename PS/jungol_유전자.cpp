#include <cstdio>
#define MAX_LEN		505
#define IFNTY		1000
#define FRONT		501
#define REAR		502

char X[MAX_LEN];
int N;
int dp[MAX_LEN][MAX_LEN];
// dp[i][j] : 인덱스 i부터 j 사이에서 삭제해야 하는 부분 서열의 수

int min2(int a, int b) {
	return a < b ? a : b;
} 

int min3(int a, int b, int c) {
	if (a < b) return min2(a, c);
	else return min2(b, c);
}

int solve(int l, int r) {
	if (l < 0 || r > N - 1 || l > r) return 0;
	if (l == r) return 1;
	if (dp[l][r] != IFNTY) return dp[l][r];

	if ((X[l] == 'a' && X[r] == 't') || (X[l] == 'g' && X[r] == 'c')) {
		dp[l][r] = solve(l + 1, r - 1);
	}
	else {
		dp[l][r] = min2(solve(l + 1, r), solve(l, r - 1)) + 1;
	}

	for (int i = l + 1; i < r - 1; ++i) {
		dp[l][r] = min2(dp[l][r], solve(l, i) + solve(i + 1, r));
	}

	return dp[l][r];
}

int main() {
	scanf("%s", X);
	// strlen
	N = 0;
	while (X[N] != '\0') N++;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			dp[i][j] = IFNTY;
		}
	}

	int ans = solve(0, N - 1);
	if (ans == IFNTY) printf("0");
	else printf("%d", N - ans);
	return 0;
}