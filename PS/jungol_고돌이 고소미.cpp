#include <iostream>
#define MAX_SZ	27
#define EMPTY	0
#define PUDDLE	1
#define NEEDLE	2
using namespace std;

typedef pair<int, int> pii;

int N;
int map[MAX_SZ][MAX_SZ];
int v[MAX_SZ][MAX_SZ][MAX_SZ][MAX_SZ];
pii male_pos, female_pos, male_house, female_house;
int q[MAX_SZ * MAX_SZ * MAX_SZ * MAX_SZ * 6];
int front = -1, rear = -1;

int dx[9] = { 0,1,1,1,0,-1,-1,-1,0 }; // 위 오른쪽위 오 오른쪽아래 아 왼쪽아래 왼 왼쪽위
int dy[9] = { -1,-1,0,1,1,1,0,-1,0 };

bool needle_check(int mi, int mj, int fi, int fj) {
	for (int dir = 0; dir < 9; ++dir) {
		int my = mi + dy[dir];
		int mx = mj + dx[dir]; 
		if (map[my][mx] == PUDDLE) continue;
		if (my == fi && mx == fj) return false;
	}
	return true;
}

int bfs() {
	int my, mx, fy, fx;

	// 고돌이 i, 고돌이 j, 고소미 i, 고소미 j, 시간
	q[++rear] = male_pos.first;
	q[++rear] = male_pos.second;
	q[++rear] = female_pos.first;
	q[++rear] = female_pos.second;
	q[++rear] = 0;

	v[male_pos.first][male_pos.second][female_pos.first][female_pos.second] = true;

	while (front != rear) {
		int mi = q[++front]; int mj = q[++front];
		int fi = q[++front]; int fj = q[++front];
		int time = q[++front];

		for (int dir1 = 0; dir1 < 9; ++dir1) {
			my = mi + dy[dir1]; 
			mx = mj + dx[dir1]; 
			if (map[my][mx] == PUDDLE || map[my][mx] == NEEDLE) continue;
			
			for (int dir2 = 0; dir2 < 9; ++dir2) {
				fy = fi + dy[dir2];
				fx = fj + dx[dir2];
				if (map[fy][fx] == PUDDLE || map[fy][fx] == NEEDLE) continue;
				if (v[my][mx][fy][fx]) continue;
				if (!needle_check(my, mx, fy, fx)) continue;
				
				if (my == male_house.first && mx == male_house.second
					&& fy == female_house.first && fx == female_house.second) 
					return time + 1;

				v[my][mx][fy][fx] = true;
				q[++rear] = my; q[++rear] = mx;
				q[++rear] = fy; q[++rear] = fx;
				q[++rear] = time + 1;
			}
		}
	}
	return -1;
}

int main() {
	cin >> N;
	cin >> male_pos.first >> male_pos.second >> male_house.first >> male_house.second;
	cin >> female_pos.first >> female_pos.second >> female_house.first >> female_house.second;
	for (int i = 0; i <= N + 1; ++i) {
		for (int j = 0; j <= N + 1; ++j) {
			if (i == 0 || j == 0 || i == N + 1 || j == N + 1) map[i][j] = PUDDLE;
			else cin >> map[i][j];
		}
	}

	if (male_pos.first == male_house.first && male_pos.second == male_house.second
		&& female_pos.first == female_house.first && female_pos.second == female_house.second)
		cout << 0;
	else cout << bfs();

	return 0;
}