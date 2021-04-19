#include <iostream>
using namespace std;

const char MAX_LEN = 101;
char tmp_num[MAX_LEN], phone_num[MAX_LEN][MAX_LEN];
int add_num, add_place;

int main() {
	bool err_flag = false;

	// 핸드폰 번호 (-)
	scanf("%s", tmp_num);

	// 더해질 숫자
	scanf(" %d", &add_num);

	// 숫자 더미의 위치
	scanf(" %d", &add_place);

	int idx = 0, place_idx = 0, n_idx = 0, ans_len = 0;
	while (tmp_num[idx] != '\0') {
		if (tmp_num[idx] == '-') {
			phone_num[place_idx][n_idx] = '\0';
			place_idx++; n_idx = 0;
		}
		else {
			if (n_idx >= 4) {
				err_flag = true;
				break;
			}
			if (place_idx == add_place - 1) {
				ans_len++;
				phone_num[place_idx][n_idx] = (char)((((tmp_num[idx] - '0') + add_num) % 10) + '0');
			}
			else {
				phone_num[place_idx][n_idx] = tmp_num[idx];
			}
			n_idx++;
		}
		idx++;
	}
	phone_num[place_idx][n_idx] = '\0';

	if (err_flag) {
		printf("%s", "INPUT ERROR!");
	}
	else {
		for (int i = 0; i < 4 - ans_len; ++i) {
			printf("%d", add_num);
		}
		printf("%s", phone_num[add_place - 1]);
	}


	return 0;
}