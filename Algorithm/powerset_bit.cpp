void powerset_bit(int n) {
	for (int i = 0; i < (1 << n); ++i) {	// (1 << n) : 2^n
		printf("{ ");						// ���� 6�� �̻��̶�� long long ���
		for (int j = 0; j < n; ++j) {
			if (i & (1 << j)) {
				printf("%d ", j + 1);
			}
		}
		printf("} \n");
	}
}
