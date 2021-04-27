#include <iostream>
#include <vector>
#define MAX_NUM	16
using namespace std;

int N;
int ans = 0;
char op[MAX_NUM];


void dfs(int cnt, int total, int cur, char buf) {
	if (cnt == N) {
		if (buf == '+') total += cur;
		else if (buf == '-') total -= cur;
		if (total == 0) {
			if (ans < 20) {
				for (int i = 1; i < N; ++i) {
					cout << i << ' ' << op[i] << ' ';
				}
				cout << N << '\n';
			}
			ans++;
		}
		return;
	}

	op[cnt] = '+';
	if (buf == '+')
		dfs(cnt + 1, total + cur, cnt + 1, '+');
	else if (buf == '-')
		dfs(cnt + 1, total - cur, cnt + 1, '+');
	
	op[cnt] = '-';
	if (buf == '+')
		dfs(cnt + 1, total + cur, cnt + 1, '-');
	else if (buf == '-')
		dfs(cnt + 1, total - cur, cnt + 1, '-');

	op[cnt] = '.';
	int tmp = cnt + 1;
	int pow = 1;
	while (tmp > 0) {
		tmp /= 10;
		pow *= 10;
	}
	dfs(cnt + 1, total, cur * pow + (cnt + 1), buf);

}


int main() {
	cin >> N;
	dfs(1, 0, 1, '+');
	cout << ans;
	return 0;
}