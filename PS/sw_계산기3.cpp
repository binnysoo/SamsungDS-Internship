#include <iostream>
using namespace std;

int infix2postfix(char *str, char *post, int len) {
	int postIdx = 0;
	for (int i = 0; i < len; ++i) {
		char ch = str[i];
		char pop_ch = ' ';

		if ('0' <= ch && ch <= '9') {
			post[postIdx++] = ch;
		}
		else if (40 <= ch && ch <= 47) {
			// op
			switch (ch) {
			case LEFT_PARENTHESES:
				stack[++top] = ch;
				break;
			case RIGHT_PARENTHESES:
				while (top >= 0) {
					pop_ch = stack[top--];
					if (pop_ch != LEFT_PARENTHESES) {
						// ??
					}
				}
			case MULTIPLY:
			case MINUS:
			case DIVIDE:
			case PLUS:
				while (top >= 0 && (Priority[ICP][ch] <= Priority[ISP][stack[top]))) {
					post[postIdx++] = stack[top--];
				}

				stack[++top] = ch;
				break;
			}
		}
	}
	while (top >= 0) {
		post[postIdx++] = stack[top--];
	}
	return postIdx;
}

int main() {
	

}