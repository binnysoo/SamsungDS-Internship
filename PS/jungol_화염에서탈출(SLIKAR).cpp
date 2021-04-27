#include <iostream>
#define EMPTY	'.'
#define FIRE	'*'
#define ROCK	'X'
#define HOUSE	'D'
#define START	'S'
#define VISITED	'v'
#define MAX_SZ	50
using namespace std;

typedef pair<int, int> pii;

int R, C;
char map[MAX_SZ][MAX_SZ];
int fidx = 0;
pii fire[MAX_SZ * MAX_SZ];
int q[MAX_SZ * MAX_SZ * 3];
int front = -1, rear = -1;

int dx[4] = { 0,1,0,-1 }; // À§ ¿À ¾Æ ¿Þ
int dy[4] = { -1,0,1,0 };

void set_fire() {
	pii tmp_fire[MAX_SZ * MAX_SZ];
	int tmp_idx = 0;
	for (int k = 0; k < fidx; ++k) {
		int i = fire[k].first; 
		int j = fire[k].second; 
		for (int dir = 0; dir < 4; ++dir) {
			int y = i + dy[dir];
			int x = j + dx[dir];
			if (y < 0 || x < 0 || y > R - 1 || x > C - 1) continue;
			if (map[y][x] == ROCK || map[y][x] == FIRE || map[y][x] == HOUSE) continue;
			map[y][x] = FIRE;
			tmp_fire[tmp_idx] = make_pair(y, x);
			tmp_idx++;
		}
	}

	for (int i = 0; i < tmp_idx; ++i) {
		fire[fidx + i] = tmp_fire[i];
	}
	fidx += tmp_idx;
}

int bfs() {
	int cur_time = 0;
	while (front != rear) {
		int i = q[++front];
		int j = q[++front];
		int time = q[++front];

		if (time > cur_time) {
			cur_time = time;
			set_fire();
		}

		if (map[i][j] == FIRE) continue; // impossible case

		for (int dir = 0; dir < 4; ++dir) {
			int y = i + dy[dir];
			int x = j + dx[dir];
			if (y < 0 || x < 0 || y > R - 1 || x > C - 1) continue;
			if (map[y][x] == ROCK || map[y][x] == FIRE || map[y][x] == VISITED) continue;
			if (map[y][x] == HOUSE) return time + 1;

			q[++rear] = y;
			q[++rear] = x;
			q[++rear] = time + 1;

			map[y][x] = VISITED;
		}
	}

	return -1;
}

int main() {
	cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> map[i][j];
			if (map[i][j] == START) {
				q[++rear] = i;
				q[++rear] = j;
				q[++rear] = 0;
			}
			else if (map[i][j] == FIRE) {
				fire[fidx] = make_pair(i, j);
				fidx++;
			}
		}
	}

	int ans = bfs();
	if (ans == -1) cout << "impossible";
	else cout << ans;

	return 0;
}