#include <cstdio>

void bit_printer(char c) {
	for (int i = 7; i >= 0; --i) {
		if (c & (1 << i))
			printf("1 ");
		else
			printf("0 ");
	}
}

int main() {
	for (int i = -5; i < 6; ++i) {
		printf("%3d : ", i);
		bit_printer((char)i);
		printf("\n");
	}
}
