#include <iostream>
#define LAND	'L'
#define WATER	'W'
#define MAX_SZ	50
#define MAX_ND	250
#define IFNTY	999999999
using namespace std;

int H, W;
char map[MAX_SZ][MAX_SZ];
int g[MAX_ND][MAX_ND];
int dx[2] = { 1,0 }; // 오른쪽 아래
int dy[2] = { 0,1 };

int main() {
	char c;
	
	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < MAX_ND; ++i) {
		for (int j = 0; j < MAX_ND; ++j) {
			if (i == j) g[i][j] = 0;
			else g[i][j] = IFNTY;
		}
	}

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == LAND) {
				int idx = i * W + j;
				for (int dir = 0; dir < 2; ++dir) {
					int x = j + dx[dir];
					int y = i + dy[dir];
					if (x < 0 || y < 0 || x > W - 1 || y > H - 1) continue;
					if (map[y][x] == LAND) {
						int tmp_idx = y * W + x;
						g[idx][tmp_idx] = g[tmp_idx][idx] = 1;
					}
				}
			}
		}
	}

	for (int k = 0; k < MAX_ND; ++k) {
		for (int i = 0; i < MAX_ND; ++i) {
			for (int j = 0; j < MAX_ND; ++j) {
				if (g[i][j] > g[i][k] + g[k][j]) {
					g[i][j] = g[i][k] + g[k][j];
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < MAX_ND; ++i) {
		for (int j = 0; j < MAX_ND; ++j) {
			if (g[i][j] == IFNTY) continue;
			if (ans < g[i][j]) ans = g[i][j];
		}
	}

	cout << ans;

	return 0;
}