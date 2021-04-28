#include <cstdio>
#define MAX_SZ 100005
#define MAX_HG 1000000

int main() {
	int N;
	int h[MAX_SZ], view[MAX_SZ];
	scanf("%d", &N);

	h[0] = MAX_HG + 5; h[N + 1] = 0;
	for (int i = 1; i <= N; ++i) view[i] = 0;

	for (int i = 1; i <= N; ++i) {
		scanf(" %d", &h[i]);
		int j = i - 1;
		while (h[j] < h[i]) {
			if (view[j] == 0) view[j] = i;
			j--;
		}
	}

	for (int i = 1; i <= N; ++i) {
		printf("%d\n", view[i]);
	}

	return 0;
}