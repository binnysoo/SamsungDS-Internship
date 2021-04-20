#include <iostream>
using namespace std;

int main() {
	int K, strike[100], ball[100], ans = 0, s, b;
	bool cand[10][10][10];
	char tmp[100][4];
	int t0, t1, t2;
	cin >> K;

	for (int q = 0; q < K; ++q) {
		cin >> tmp[q] >> strike[q] >> ball[q];
	}

	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j < 10; ++j) {
			if (i == j) continue;
			for (int k = 1; k < 10; ++k) {
				if (i == k || j == k) continue;
				bool flag = true;
				for (int q = 0; q < K; ++q) {
					t0 = tmp[q][0] - '0';
					t1 = tmp[q][1] - '0';
					t2 = tmp[q][2] - '0';
					s = b = 0;

					if (t0 == i) s++;
					if (t1 == j) s++;
					if (t2 == k) s++;

					if (t0 == j || t0 == k) b++;
					if (t1 == i || t1 == k) b++;
					if (t2 == i || t2 == j) b++;

					if (s != strike[q] || b != ball[q]) {
						flag = false;
						break;
					}		   
				}
				if (flag)
					ans++;
			}
		}
	}

	cout << ans;

	return 0;
}