#include <iostream>
using namespace std;

typedef pair<int, int> pii;
enum { EAST = 1, WEST, SOUTH, NORTH };
pii coord[10];

int main() {
	int K, area = 0;
	cin >> K;
	
	pii point = { 0,0 };
	int idx = 0, dir, len;
	int max_w = 0, max_h = 0;

	coord[idx++] = point;
	for (int i = 0; i< 6; ++i) {
		point = coord[idx - 1];
		cin >> dir >> len;
		switch (dir) {
		case EAST:
			point.first += len;
			if (max_w < len) max_w = len;
			break;
		case WEST:
			point.first -= len;
			if (max_w < len) max_w = len;
			break;
		case SOUTH:
			point.second -= len;
			if (max_h < len) max_h = len;
			break;
		case NORTH:
			point.second += len;
			if (max_h < len) max_h = len;
			break;
		}
		coord[idx++] = point;
	}

	// sort
	for (int i = 1; i < 6; ++i) {
		pii tmp = coord[i];
		int j = i - 1;
		while (j >= 0 && coord[j].first > tmp.first) {
			coord[j + 1] = coord[j];
			j--;
		}
		while (j >= 0 && coord[j].first == tmp.first && coord[j].second > tmp.second) {
			coord[j + 1] = coord[j];
			j--;
		}
		coord[j + 1] = tmp;
	}


	int inner1, inner2;
	if (coord[3].first == coord[2].first) {
		inner1 = coord[3].second - coord[2].second;
	}
	else {
		inner1 = coord[3].first - coord[2].first;
	}

	// sort
	for (int i = 1; i < 6; ++i) {
		pii tmp = coord[i];
		int j = i - 1;
		while (j >= 0 && coord[j].second > tmp.second) {
			coord[j + 1] = coord[j];
			j--;
		}
		while (j >= 0 && coord[j].second == tmp.second && coord[j].first > tmp.first) {
			coord[j + 1] = coord[j];
			j--;
		}
		coord[j + 1] = tmp;
	}
	if (coord[3].first == coord[2].first) {
		inner2 = coord[3].second - coord[2].second;
	}
	else {
		inner2 = coord[3].first - coord[2].first;
	}

	area = max_h * max_w - inner1 * inner2;

	cout << K * area;
	return 0;
} 