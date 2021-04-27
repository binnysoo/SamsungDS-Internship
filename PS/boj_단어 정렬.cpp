#include <cstdio>
#define MAX_LEN		55
#define MAX_NUM		20000
char str[MAX_NUM][MAX_LEN];
char L[MAX_NUM][MAX_LEN], R[MAX_NUM][MAX_LEN];

int str_len(char *str) {
	int idx = 0;
	while (str[idx] != '\0') idx++;
	return idx;
}

int str_cmp(char *a, char *b) { 
	int alen = str_len(a);
	int blen = str_len(b);
	int i;

	if (alen < blen) return 1;
	else if (alen > blen) return -1;
	else {
		for (i = 0; i < alen && i < blen; ++i) {
			if (a[i] < b[i]) return 1;
			else if (a[i] > b[i]) return -1;
		}
	}
	return 0;
}

void str_cpy(char *a, char *b) {
	int alen = str_len(a);
	for (int i = 0; i < alen; ++i) {
		b[i] = a[i];
	}
	b[alen] = '\0';
}

void merge(int l, int m, int r) {
	int llen = m - l + 1;
	int rlen = r - m;

	for (int i = 0; i < llen; ++i) {
		str_cpy(str[l + i], L[i]);
	}
	for (int i = 0; i < rlen; ++i) {
		str_cpy(str[m + 1 + i], R[i]);
	}

	int i = 0, j = 0, k = l;
	while (i < llen && j < rlen) {
		int comp = str_cmp(L[i], R[j]);
		if (comp == 1) {
			str_cpy(L[i], str[k]);
			i++;
		}
		else if (comp == -1) {
			str_cpy(R[j], str[k]);
			j++;
		}
		else if (comp == 0) {
			str[k][0] = '\0';
			i++;
		}
		k++;
	}

	while (i < llen) {
		str_cpy(L[i], str[k]);
		i++; k++;
	}
	while (j < rlen) {
		str_cpy(R[j], str[k]);
		j++; k++;
	}
}

void merge_sort(int l, int r) {
	if (l >= r) return;
	int m = l + (r - l) / 2;
	merge_sort(l, m);
	merge_sort(m + 1, r);
	merge(l, m, r);
}

int main() {
	char tmp[55];
	int N, n = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf(" %s", str[i]);
	}

	merge_sort(0, N - 1);
	 
	for (int i = 0; i < N; ++i) {
		if (str[i][0] == '\0') continue;
		printf("%s\n", str[i]);
	}
} 