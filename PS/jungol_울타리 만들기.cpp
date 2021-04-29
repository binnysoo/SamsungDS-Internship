#include <iostream>
#include <stack>
#define MAX_SZ	100
using namespace std;

typedef pair<int, int> pii;

/*
  0: 일직선상
양수: 반시계방향
음수: 시계방향
*/
int ccw(pii p1, pii p2, pii p3) {
	int a = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second;
	int b = p1.second * p2.first + p2.second * p3.first + p3.second * p1.first;
	return a - b;
}

pii next_to_top(stack<pii> s) {
	pii ret, tmp;
	tmp = s.top(); s.pop();
	ret = s.top();
	s.push(tmp);
	return ret;
}

int distSq(pii p1, pii p2) {
	return (p1.first - p2.first)*(p1.first - p2.first) +
		(p1.second - p2.second)*(p1.second - p2.second);
}

int orientation(pii p, pii q, pii r)
{
	int val = (q.second - p.second) * (r.first - q.first) -
		(q.first - p.first) * (r.second - q.second);

	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

int compare(pii *arr, pii p1, pii p2) {
	// Find orientation
	int o = orientation(arr[0], p1, p2);
	if (o == 0)
		return (distSq(arr[0], p2) >= distSq(arr[0], p1)) ? -1 : 1;

	return (o == 2) ? -1 : 1;
}

void merge_sort(pii *arr, int l, int r) {
	if (l >= r) return;

	int m = (l + r) / 2;
	merge_sort(arr, l, m);
	merge_sort(arr, m + 1, r);

	// merge
	pii L[MAX_SZ], R[MAX_SZ];
	int lidx = m - l + 1;
	int ridx = r - m;

	for (int i = 0; i < lidx; ++i) L[i] = arr[l + i];
	for (int j = 0; j < ridx; ++j) R[j] = arr[m + 1 + j];

	int i = 0, j = 0, k = l;
	while (i < lidx && j < ridx) {
		int langle = (arr[0].second - L[i].second) / (arr[0].first - L[i].first);
		int rangle = (arr[0].second - R[j].second) / (arr[0].first - R[j].first);

		if (compare(arr, L[i], R[j]) == -1) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < lidx) {
		arr[k] = L[i];
		i++; k++;
	}
	while (j < ridx) {
		arr[k] = R[j];
		j++; k++;
	}
}

int main() {
	int n;
	pii point[MAX_SZ];
	stack<pii> s;

	cin >> n;

	int x, y;
	int ymin = 10005, idx;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y;
		point[i] = make_pair(x, y);
		if (ymin > y) {
			ymin = y;
			idx = i;
		}
	}
	pii tmp = point[idx];
	point[idx] = point[0];
	point[0] = tmp;

	merge_sort(point, 1, n - 1);

	s.push(point[0]);
	s.push(point[1]);
	s.push(point[2]);

	for (int i = 3; i < n; ++i) {
		while (ccw(next_to_top(s), s.top(), point[i]) <= 0) {
			s.pop();
		}
		s.push(point[i]);
	}

	cout << s.size() << '\n';

	stack<pii> ans;
	while (!s.empty()) {
		ans.push(s.top()); s.pop();
	}

	while (!ans.empty()) {
		cout << ans.top().first << ' ' << ans.top().second << '\n';
		ans.pop();
	}

	return 0;
}