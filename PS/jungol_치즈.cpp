#include <iostream>
#define make_piii(i, j, x) make_pair(make_pair(i, j), x)
using namespace std;

typedef pair<pair<int, int>, int> piii;
const int MAX_SZ = 100;
const int CHEESE = -1;
int H, W;
int map[MAX_SZ][MAX_SZ], cnt[MAX_SZ * MAX_SZ];
bool visit[MAX_SZ][MAX_SZ];
piii q[MAX_SZ * MAX_SZ];
int front = -1, rear = -1;

int dx[4] = { 0,1,0,-1 }; // À§ ¿À ¾Æ ¿Þ
int dy[4] = { -1,0,1,0 };

bool not_range(int i, int j) {
	if (i < 0 || j < 0 || i > H - 1 || j > W - 1) return true;
	return false;
}

void bfs() {
	int i, j, y, x, cnt;
	piii cur;

	while (front != rear) {
		cur = q[++front];
		i = cur.first.first; j = cur.first.second; cnt = cur.second;
		for (int dir = 0; dir < 4; ++dir) {
			y = i + dy[dir]; x = j + dx[dir];
			if (not_range(y, x) || visit[y][x]) continue;
			if (map[y][x] == CHEESE) {
				map[y][x] = cnt + 1;
			}
			else if (map[y][x] == 0) {
				q[++rear] = make_piii(y, x, cnt);
				visit[y][x] = true;
			}
		}
	}

	return;
}

int main() {
	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> map[i][j];
			map[i][j] *= -1;
			if (i == 0 || j == 0 || i == H - 1 || j == W - 1) {
				q[++rear] = make_piii(i, j, 0);
			}
		}
	}
    
    int ans = 0;
	while (front != rear) {
		ans++;
		bfs();
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				if (map[i][j] == ans) {
					q[++rear] = make_piii(i, j, map[i][j]);
				}
			}
		}
	}
	ans--;

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cnt[map[i][j]]++;
			if (ans < map[i][j]) ans = map[i][j];
		}
	}

	cout << ans << '\n' << cnt[ans];

	return 0;
}