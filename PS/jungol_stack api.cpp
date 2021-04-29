/// === user.cpp ===

#ifndef NULL
#define NULL 0
#endif
const int SIZE = 100010;
struct Node {
	int num;
	Node* next;
}buf[SIZE];
int bcnt;

struct Stack {
	Node*head;
	int cnt;
}stkObject;

Stack* newStack() {
	bcnt = 0;
	Stack *stk = new Stack;
	stk->cnt = 0;
	stk->head = &buf[bcnt];

	return stk;
}

void delStack(Stack*stk) {
	delete(stk);
}

bool empty(Stack*stk) {
	if (stk->cnt <= 0) return true;
	return false;
}

int size(Stack*stk) {
	return stk->cnt;
}

int top(Stack*stk) {
	return stk->head->num;
}

void push(Stack*stk, int num) {
	buf[bcnt].num = num;
	stk->head = &buf[bcnt];
	bcnt++;
	stk->cnt++;
}

void pop(Stack*stk) {
	if (empty(stk)) return;
	bcnt--;
	stk->head = &buf[bcnt - 1];
	stk->cnt--;
}



/// === main.cpp ===
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct Node Node;
typedef struct Stack Stack;

extern Stack* newStack();
extern void delStack(Stack*stk);

extern bool empty(Stack*stk);
extern int size(Stack*stk);
extern int top(Stack*stk);
extern void push(Stack*stk, int);
extern void pop(Stack*stk);


int main() {
	//    freopen("input.txt", "r", stdin);
	//    freopen("output.txt", "w", stdout);

	setbuf(stdout, NULL);

	Stack* stk = newStack();
	int N;
	char cmd[10];
	int num, i;
	scanf("%d", &N);
	for (i = 0; i < N; ++i) {
		scanf("%s", cmd);
		if (cmd[0] == 'e') {             /// 1. empty
			printf("%d\n", empty(stk));
		}
		else if (cmd[0] == 's') {        /// 2. size
			int ret = size(stk);
			printf("%d\n", ret);
		}
		else if (cmd[0] == 't') {        /// 3. top
			if (empty(stk)) {
				puts("except!");
			}
			else {
				printf("%d\n", top(stk));
			}
		}
		else {
			if (cmd[1] == 'u') {         /// 4. push
				scanf("%d", &num);
				push(stk, num);
			}
			else {                      /// 5. pop
				pop(stk);
			}
		}
	}

	delStack(stk);
	return 0;
}
