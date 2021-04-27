#include <cstdio>
#define MAX_NUM		5005
using namespace std;

const float PI = 3.141;

int N;
float x, y;
float dist[2][MAX_NUM];
float radar_x[2], radar_y[2], max_radius, K;
int key = 1000;
int min_num = 999999999;

int main() {
	scanf("%d", &N);
	scanf(" %f %f %f %f %f", &radar_x[0], &radar_y[0], &radar_x[1], &radar_y[1], &K);

	max_radius = (K / PI) * key;

	for (int j = 0; j < N; ++j) {
		scanf(" %f %f", &x, &y);
		for (int i = 0; i < 2; ++i) {
			float x_dist = radar_x[i] - x;
			float y_dist = radar_y[i] - y;
			dist[i][j] = (x_dist * x_dist + y_dist * y_dist) * key;
		}
	}

	for (int i = 0; i <= max_radius; ++i) {
		int cnt = 0;
		double r1 = i;
		double r2 = max_radius - i;

		for (int j = 0; j < N; j++) {
			if (dist[0][j] > r1 && dist[1][j] > r2) {
				cnt++;
			}
		}
		if (cnt < min_num) min_num = cnt;
	}

	printf("%d", min_num);

	return 0;
} 