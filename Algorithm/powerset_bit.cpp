void powerset_bit(int n) {
	for (int i = 0; i < (1 << n); ++i) {	// (1 << n) : 2^n
		printf("{ ");						// 만약 6개 이상이라면 long long 사용
		for (int j = 0; j < n; ++j) {
			if (i & (1 << j)) {
				printf("%d ", j + 1);
			}
		}
		printf("} \n");
	}
}
