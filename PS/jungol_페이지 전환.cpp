#include <iostream>
using namespace std;

const int MAX_SZ = 505;
const int IFNTY = 999999999;
int N;
int dist[MAX_SZ][MAX_SZ];

int main() {
	int i, j, k, max_pg = 0;
	cin >> N;

	for (i = 0; i < MAX_SZ; ++i) {
		for (j = 0; j < MAX_SZ; ++j) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = IFNTY;
		}
	}
	for (k = 0; k < N; ++k) {
		cin >> i >> j;
		dist[i][j] = 1;
		if (i > max_pg) max_pg = i;
		if (j > max_pg) max_pg = j;
	}

	for (k = 1; k <= max_pg; ++k) {
		for (i = 1; i <= max_pg; ++i) {
			if (i == k) continue;
			for (j = 1; j <= max_pg; ++j) {
				if (i == j || k == j) continue;
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	float total = 0.0;
	float div = max_pg * (max_pg - 1);
	for (i = 1; i <= max_pg; ++i) {
		for (j = 1; j <= max_pg; ++j) {
			if (i == j) continue;
			total += dist[i][j];
		}
	}

	printf("%.3f", total / div);

	return 0;
}