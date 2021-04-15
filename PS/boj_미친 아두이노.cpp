#include <cstdio>
#include <vector>
#define MAX_SZ	100
using namespace std;
typedef pair<int, int> pii;

int R, C;
char map[MAX_SZ][MAX_SZ];
vector<pii> crazy;

int get_dir(pii a, pii b) {
	// 북동(9) 또는 오른쪽(6) 또는 남동(3)
	if (a.second < b.second) {
		if (a.first > b.first)
			return 9;
		else if (a.first == b.first)
			return 6;
		else
			return 3;
	}
	// 위(8) 또는 아래(2)
	else if (a.second == b.second) {
		if (a.first > b.first)
			return 8;
		else
			return 2;
	}
	// 남서(1) 또는 왼쪽(4) 또는 북서(7)
	else { // a.first > b.first
		if (a.first > b.first)
			return 7;
		else if (a.first == b.first)
			return 4;
		else
			return 1;
	}
}

void update_axis(int dir_code, pii *axis) {
	switch (dir_code) {
	case 1:
		axis->second--;
		axis->first++;
		break;
	case 2:
		axis->first++;
		break;
	case 3:
		axis->second++;
		axis->first++;
		break;
	case 4:
		axis->second--;
		break;
	case 6:
		axis->second++;
		break;
	case 7:
		axis->second--;
		axis->first--;
		break;
	case 8:
		axis->first--;
		break;
	case 9:
		axis->second++;
		axis->first--;
		break;
	}
}

void check_dup_and_move() {
	int x, y;
	int index;
	vector<pii> update;
	for (int i = 0; i < crazy.size(); ++i) {
		x = crazy[i].first;
		y = crazy[i].second;
		if (x == -1 || y == -1) continue;
		if (map[x][y] == '.')
			map[x][y] = (char)(i + 1); // 인덱스가 0인 경우가 있어 +1 한 값 저장
		else {
			crazy[i] = { -1, -1 };
			index = ((int)map[x][y] - 1);
			crazy[index] = { -1, -1 };
			update.push_back({ x, y });
		}
	}
	for (pii axis : update)
		map[axis.first][axis.second] = '.';
}

bool check_end() {
	int x, y;
	for (int i = 0; i < crazy.size(); ++i) {
		x = crazy[i].first;
		y = crazy[i].second;
		if (map[x][y] == 'I') return true;
	}
	return false;
}

void print_map() {
	int i, j;
	for (i = 0; i < R; ++i) {
		for (j = 0; j < C; ++j) {
			if (map[i][j] != 'I' && map[i][j] != '.')
				printf("%c", 'R');
			else printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int i, j;
	char dir[MAX_SZ];
	bool print_flag = true;
	pii jongsoo;

	scanf(" %d %d", &R, &C);
	for (i = 0; i < R; ++i) {
		for (j = 0; j < C; ++j) {
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'R') {
				crazy.push_back({ i, j });
				// 'R' 대신 아두이노 인덱스 번호 표기
				map[i][j] = (char)(crazy.size() - 1); 
			}
			else if (map[i][j] == 'I') {
				jongsoo = { i, j };
			}
		}
	}

	scanf("%s", dir);

	// 현재 위치를 기준으로 아두이노는 움직이게 됨
	// 현재 좌표점 기준으로 각 아두이노가 옮겨갈 장소(또는 방향) 계산
	// 아두이노끼리 겹치는 경우 아두이노 파괴 
	// (단, 2개 이상의 아두이노가 겹칠 가능성이 있으므로 모든 아두이노에 대하여 계산을 완료한 후에 파괴할 것)
	// 아두이노의 자리 계산 후 종수 이동 (jongsoo 업데이트)
	// 만약 아두이노와 종수가 겹친다면 프로그램을 종료하고 kraj X 를 출력

	int idx = 0;
	while (dir[idx] != '\0') {
		for (i = 0; i < crazy.size();++i) {
			if (crazy[i].first == -1 && crazy[i].second == -1) 
				continue;
			map[crazy[i].first][crazy[i].second] = '.';
			update_axis(get_dir(crazy[i], jongsoo), &crazy[i]);
		} // 미친 아두이노들 자리 이동 완료!

		// 이제 종수 이동
		map[jongsoo.first][jongsoo.second] = '.';
		update_axis(dir[idx] - '0', &jongsoo);
		map[jongsoo.first][jongsoo.second] = 'I';

		// 종수가 잡히면 게임 종료
		if (check_end()) {
			if (dir[idx] - '0' == 5)
				printf("kraj %d", idx);
			else
				printf("kraj %d", idx + 1);
			print_flag = false;
			break;
		}

		// 아두이노간 동일한 좌표가 있는지 확인
		check_dup_and_move();

		// for debugging purpose
		print_map();
		printf("-----------------\n");
		// end

		idx++;
	}

	if (print_flag)
		print_map();

	return 0;
}
