#include <iostream>
#define MAX_SZ	105
#define START	1
#define IFNTY	999999999
using namespace std;

int N, M;
int w[MAX_SZ][MAX_SZ], dist[MAX_SZ], route[MAX_SZ];
bool v[MAX_SZ];

int get_pos() {
	int min_dist = IFNTY, pos = -1;
	for (int i = 1; i <= N; ++i) {
		if (v[i]) continue;
		if (dist[i] < min_dist) {
			min_dist = dist[i];
			pos = i;
		}
	}
	return pos;
}

void dijkstra() {
	int pos = START;
	do {
		v[pos] = true;
		for (int adj = 1; adj <= N; ++adj) {
			if (v[adj] || pos == adj) continue;
			if (dist[adj] > dist[pos] + w[pos][adj]) {
				dist[adj] = dist[pos] + w[pos][adj];
				route[adj] = pos;
			}
		}
		pos = get_pos();
	} while (pos != -1);
}


int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> w[i][j];
		}
		dist[i] = IFNTY;
	}

	dist[START] = 0;
	dijkstra();

	cout << dist[M] << '\n';
	
	// get route
	int stack[MAX_SZ];
	int top = -1;
	int pos = M;
	while (pos != 0) {
		stack[++top] = pos;
		pos = route[pos];
	}
	while (top != -1) {
		cout << stack[top--] << ' ';
	}


	return 0;
}