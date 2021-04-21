#include <iostream>
#define MAX_SZ 100
using namespace std;

int M, N, K;
bool sq[MAX_SZ][MAX_SZ];
int idx = 0;
int cnt[MAX_SZ] = { 0, };

int dx[4] = { 1, 0, -1, 0 }; // ¿À ¾Æ ¿Þ À§
int dy[4] = { 0,1,0,-1 };

void dfs(int i, int j, int idx) {
	sq[i][j] = true;
	cnt[idx]++;
	for (int dir = 0; dir < 4; ++dir) {
		int y = i + dy[dir];
		int x = j + dx[dir];
		if (y < 0 || x < 0 || y > M - 1 || x > N - 1) continue;
		if (sq[y][x]) continue;
		dfs(y, x, idx);
	}

}

void insertion_sort(int idx) {
	for (int i = 1; i < idx; ++i) {
		int tmp = cnt[i];
		int j = i - 1;
		while (j >= 0 && cnt[j] > tmp) {
			cnt[j + 1] = cnt[j];
			j--;
		}
		cnt[j + 1] = tmp;
	}
}

int main() {
	int x1, x2, y1, y2;
	cin >> M >> N >> K;
	for (int i = 0; i < K; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		for (int j = y1; j < y2; ++j) {
			for (int k = x1; k < x2; ++k) {
				sq[j][k] = true;
			}
		}
	}
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			if (!sq[i][j]) {
				dfs(i, j, idx);
				idx++;
			}
		}
	}

	insertion_sort(idx);

	cout << idx << '\n';
	for (int i = 0; i < idx; ++i) cout << cnt[i] << ' ';

	return 0;
}