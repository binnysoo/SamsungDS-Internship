#include <iostream>
#include <cmath>
#define ROOT	1
using namespace std;

int SIZE, LEAF;
int N, Q;
long long int *st;

/*********
- ss, se : segment tree start, segment tree end
- qs, qe : query start, query end
- si	 : segment tree index
*********/

/* 트리 업데이트 */
void update(int ss, int se, int idx, int diff, int si) {
	if (idx < ss || idx > se)
		return;

	st[si] += diff;
	if (ss != se) {
		int mid = (ss + se) / 2;
		update(ss, mid, idx, diff, si * 2);
		update(mid + 1, se, idx, diff, si * 2 + 1);
	}
}

/* 트리 구간 합 구하기 */
long long int get_sum(int ss, int se, int qs, int qe, int si) {
	// fully included
	if (qs <= ss && qe >= se)
		return st[si];
	// out of range
	if (se < qs || ss > qe)
		return 0;
	// partially included
	int mid = (ss + se) / 2;
	return get_sum(ss, mid, qs, qe, si * 2)
		+ get_sum(mid + 1, se, qs, qe, si * 2 + 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int N, Q, type, p, q, x;
	cin >> N >> Q;

	SIZE = pow(2, ceil(log2(N) + 1));
	LEAF = SIZE / 2;

	st = (long long int*)calloc(SIZE, sizeof(long long int)); // 0으로 초기화

	for (int i = 0; i < Q; ++i) {
		cin >> type;
		if (type == 1) {
			cin >> p >> x;
			update(1, N, p, x, ROOT);
		}
		else if (type == 2) {
			cin >> p >> q;
			cout << get_sum(1, N, p, q, ROOT) << '\n';
		}
	}

	free(st);

	return 0;
}