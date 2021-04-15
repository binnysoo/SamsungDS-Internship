#include <cstdio>
#include <vector>
#define MAX_SZ	100
using namespace std;
typedef pair<int, int> pii;

int R, C;
char map[MAX_SZ][MAX_SZ];
vector<pii> crazy;

int get_dir(pii a, pii b) {
	// �ϵ�(9) �Ǵ� ������(6) �Ǵ� ����(3)
	if (a.second < b.second) {
		if (a.first > b.first)
			return 9;
		else if (a.first == b.first)
			return 6;
		else
			return 3;
	}
	// ��(8) �Ǵ� �Ʒ�(2)
	else if (a.second == b.second) {
		if (a.first > b.first)
			return 8;
		else
			return 2;
	}
	// ����(1) �Ǵ� ����(4) �Ǵ� �ϼ�(7)
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
			map[x][y] = (char)(i + 1); // �ε����� 0�� ��찡 �־� +1 �� �� ����
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
				// 'R' ��� �Ƶ��̳� �ε��� ��ȣ ǥ��
				map[i][j] = (char)(crazy.size() - 1); 
			}
			else if (map[i][j] == 'I') {
				jongsoo = { i, j };
			}
		}
	}

	scanf("%s", dir);

	// ���� ��ġ�� �������� �Ƶ��̳�� �����̰� ��
	// ���� ��ǥ�� �������� �� �Ƶ��̳밡 �Űܰ� ���(�Ǵ� ����) ���
	// �Ƶ��̳볢�� ��ġ�� ��� �Ƶ��̳� �ı� 
	// (��, 2�� �̻��� �Ƶ��̳밡 ��ĥ ���ɼ��� �����Ƿ� ��� �Ƶ��̳뿡 ���Ͽ� ����� �Ϸ��� �Ŀ� �ı��� ��)
	// �Ƶ��̳��� �ڸ� ��� �� ���� �̵� (jongsoo ������Ʈ)
	// ���� �Ƶ��̳�� ������ ��ģ�ٸ� ���α׷��� �����ϰ� kraj X �� ���

	int idx = 0;
	while (dir[idx] != '\0') {
		for (i = 0; i < crazy.size();++i) {
			if (crazy[i].first == -1 && crazy[i].second == -1) 
				continue;
			map[crazy[i].first][crazy[i].second] = '.';
			update_axis(get_dir(crazy[i], jongsoo), &crazy[i]);
		} // ��ģ �Ƶ��̳�� �ڸ� �̵� �Ϸ�!

		// ���� ���� �̵�
		map[jongsoo.first][jongsoo.second] = '.';
		update_axis(dir[idx] - '0', &jongsoo);
		map[jongsoo.first][jongsoo.second] = 'I';

		// ������ ������ ���� ����
		if (check_end()) {
			if (dir[idx] - '0' == 5)
				printf("kraj %d", idx);
			else
				printf("kraj %d", idx + 1);
			print_flag = false;
			break;
		}

		// �Ƶ��̳밣 ������ ��ǥ�� �ִ��� Ȯ��
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
