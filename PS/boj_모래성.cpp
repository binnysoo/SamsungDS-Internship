#include <iostream>
#define MAX_SZ				1000
#define WAVE				-1
#define make_piii(i, j, x)	make_pair(make_pair(i, j), x)
using namespace std;

typedef pair<pair<int, int>, int> piii;
int H, W;
int map[MAX_SZ][MAX_SZ];
bool v[MAX_SZ][MAX_SZ];
piii q[MAX_SZ * MAX_SZ], vanish[MAX_SZ * MAX_SZ];
int front = -1, rear = -1, vf = -1, vr = -1;

int dx[8] = { 0,1,1,1,0,-1,-1,-1 }; // 위 오른쪽위 오 오른쪽아래 아래 왼쪽아래 왼쪽 왼쪽위
int dy[8] = { -1,-1,0,1,1,1,0,-1 };

void print_map() {
	cout << '\n';
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (map[i][j] == -1) cout << '.';
			else cout << map[i][j];
		}
		cout << '\n';
	}
}

void bfs() {
	int i, j, cnt;
	// while queue is not empty
	while (front != rear) {
		piii cur = q[++front];
		i = cur.first.first; j = cur.first.second; cnt = cur.second;
		for (int dir = 0; dir < 8; ++dir) {
			int y = i + dy[dir]; 
			int x = j + dx[dir];
			if (y < 0 || x < 0 || y > H - 1 || x > W - 1) continue; // out of range
			if (v[y][x]) continue; // visited
			
			if (map[y][x] == WAVE) {
				q[++rear] = make_piii(y, x, cnt);
				v[y][x] = true;
			}
			else if (map[y][x] > 0) {
				map[y][x]--;
				if (map[y][x] == 0) vanish[++vr] = make_piii(y, x, cnt);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	char c;
	cin >> H >> W;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			cin >> c;
			if (c == '.') {
				map[i][j] = -1;
				// add to queue
				q[++rear] = make_piii(i, j, 0);
				v[i][j] = true;
			}
			else 
				map[i][j] = c - '0';
		}
	}

	int cnt = -1;
	while (front != rear) {
		bfs();
		while (vf != vr) {
			q[++rear] = vanish[++vf];
		}
		cnt++;
	}

	cout << cnt;

	return 0;
}