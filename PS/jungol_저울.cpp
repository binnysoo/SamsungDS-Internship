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

	int ans = 0; // ans = 최대로 만들 수 있는 무게 (아무것도 담지 않는 경우 0이므로 0으로 초기화)
	for (i = 1; i <= N; ++i) {
		if (ans + 1 < w[i]) break; // 만약 최대로 만들 수 있는 무게 + 1 (+ 1을 하는 이유는 만들 수 없는 "최소" 무게를 구해야 하므로) 이 다음으로 무거운 추보다 가볍다면, 
		ans += w[i];
	}

	cout << ans + 1;

	return 0;
}