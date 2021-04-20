#include <iostream>
using namespace std;

int arr[5] = { 1,2,3,4,5 };
int t[5] = {};

void printArray(int *a, int n) {
	for (int i = 0; i < n; ++i) {
		cout << a[i];
	}
}

void nCr(int n, int r, int q) {
	if (r == 0) {
		// »ÌÀ»¸¸Å­ ´Ù »ÌÀº °æ¿ì
		printArray(t, q);
	}
	else if (n < r)
		return;
	else {
		t[r - 1] = arr[n - 1];
		nCr(n - 1, r - 1, q);
		nCr(n - 1, r, 1);
	}
}

void nHr(int n, int r, int q) {
	if (r == 0) {
		// »ÌÀ»¸¸Å­ ´Ù »ÌÀº °æ¿ì
		printArray(t, q);
	}
	else if (n < 1)
		return;
	else {
		t[r - 1] = arr[n - 1];
		nHr(n, r - 1, q);
		nHr(n - 1, r, 1);
	}
}

int main() {

	return 0;
}