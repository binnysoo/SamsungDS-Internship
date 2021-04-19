#include <iostream>
using namespace std;

const int MAX_NUM = 1005;
const int MAX_W = 1000001;
int N, ans = 1;
int w[MAX_NUM];
bool result[MAX_W];


int main() {
	int i, j;
	cin >> N;
	w[0] = 0; result[0] = true;
	for (i = 1; i <= N; ++i) {
		cin >> w[i];
		result[w[i]] = true;
	}

	// sort
	int tmp;
	for (i = 2; i <= N; ++i) {
		tmp = w[i]; j = i - 1;
		while (j > 0 && w[j] > tmp) {
			w[j + 1] = w[j];
			j--;
		}
		w[j + 1] = tmp;
	}

	int ans = 0; // ans = �ִ�� ���� �� �ִ� ���� (�ƹ��͵� ���� �ʴ� ��� 0�̹Ƿ� 0���� �ʱ�ȭ)
	for (i = 1; i <= N; ++i) {
		if (ans + 1 < w[i]) break; // ���� �ִ�� ���� �� �ִ� ���� + 1 (+ 1�� �ϴ� ������ ���� �� ���� "�ּ�" ���Ը� ���ؾ� �ϹǷ�) �� �������� ���ſ� �ߺ��� �����ٸ�, 
		ans += w[i];
	}

	cout << ans + 1;

	return 0;
}