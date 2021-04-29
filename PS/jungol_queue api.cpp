#ifndef NULL
#define NULL 0
#endif
const int SIZE = 100010;
struct Node {
	int num;
	Node* next;
}buf[SIZE];
int bcnt;

struct Queue {
	Node*head, *tail;
	int cnt;
}que;

Queue* newQueue() {
	bcnt = 0;
	buf[bcnt].next = NULL;

	Queue* que = new Queue;
	que->cnt = 0;
	que->head = &buf[bcnt];
	que->tail = &buf[bcnt];
	return que;
}

void delQueue(Queue*que) {
	delete(que);
}

bool empty(Queue*que) {
	if (que->cnt <= 0) return true;
	return false;
}

int size(Queue*que) {
	return que->cnt;
}

int front(Queue*que) {
	return que->head->num;
}

int back(Queue*que) {
	return que->tail->num;
}

void push(Queue*que, int num) {
	buf[bcnt].num = num;
	que->tail->next = &buf[bcnt];
	que->tail = &buf[bcnt];
	bcnt++;
	que->cnt++;
}

void pop(Queue*que) {
	if (empty(que)) return;
	que->head = &buf[bcnt - que->cnt + 1];
	que->cnt--;
}


/// === main.cpp ===
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct Queue Queue;

extern Queue* newQueue();
extern void delQueue(Queue*que);

extern bool empty(Queue*que);
extern int size(Queue*que);
extern int front(Queue*que);
extern int back(Queue*que);
extern void push(Queue*que, int);
extern void pop(Queue*que);


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	setbuf(stdout, NULL);

	Queue* que = newQueue();
	int N;
	char cmd[10];
	int num, i;
	scanf("%d", &N);
	for (i = 0; i < N; ++i) {
		scanf("%s", cmd);
		if (cmd[0] == 'e') {             /// 1. empty
			printf("%d\n", empty(que));
		}
		else if (cmd[0] == 's') {        /// 2. size
			int ret = size(que);
			printf("%d\n", ret);
		}
		else if (cmd[0] == 'f') {        /// 3. front
			if (empty(que)) {
				puts("except!");
			}
			else {
				printf("%d\n", front(que));
			}
		}
		else if (cmd[0] == 'b') {        /// 4. back
			if (empty(que)) {
				puts("except!");
			}
			else {
				printf("%d\n", back(que));
			}
		}
		else {
			if (cmd[1] == 'u') {         /// 5. push
				scanf("%d", &num);
				push(que, num);
			}
			else {                      /// 6. pop
				pop(que);
			}
		}
	}

	delQueue(que);
	return 0;
}
