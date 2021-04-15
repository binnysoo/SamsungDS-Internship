#include <iostream>
#define MAX_LEN		10000
#define INSERT		'I'
#define DELETE		'D'
#define ADD			'A'
using namespace std;

typedef struct _node {
	int val;
	int idx;
	struct _node *next;
} node;
typedef node * nodePtr;

nodePtr new_node(int val, int idx, nodePtr next) {
	nodePtr new_node = new node();
	new_node->val = val;
	new_node->idx = idx;
	new_node->next = next;
	return new_node;
}

void insert_node(nodePtr head, nodePtr new_node) {
	if (head == NULL) {
		head = new_node;
	}
	else {
		nodePtr tmp, prev = new node();
		tmp = head, prev = NULL;
		while (tmp != NULL && tmp->idx < new_node->idx) {
			prev = tmp;
			tmp = tmp->next;
		}
		if (prev == NULL) {
			head = new_node;
		}
		else {
			prev->next = new_node;
		}
		new_node->next = tmp;
	}
}

void delete_node(nodePtr head, int from, int to) {
	nodePtr tmp = head, prev = NULL;
	while (tmp != NULL) {
		if (tmp->idx >= from && tmp->idx < to) {
			if (prev == NULL) {
				head = tmp->next;
			}
			else {
				prev->next = tmp;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int ith_node(nodePtr head, int idx) {
	nodePtr tmp = head;
	while (idx != tmp->idx) {
		tmp = tmp->next;
	}
	return tmp->val;
}

void reindex_node(nodePtr head, int from, int change) {
	nodePtr tmp = head;
	while (tmp != NULL && from > tmp->idx) {
		tmp = tmp->next;
	}
	while (tmp != NULL) {
		tmp->idx += change;
		tmp = tmp->next;
	}
}

void print_result(int *idx, int *code, nodePtr head, int n) {
	for (int i = 0; i < n; ++i) {
		if (idx[i] != -1) {
			cout << code[idx[i]] << ' ';
		}
		else {
			cout << ith_node(head, i) << ' ';
		}
	}
}

int main() {
	int tc, len, N, added;
	int i, j, x, y, s, front, rear, cnt1, cnt2;
	int code[MAX_LEN], idx[MAX_LEN];
	nodePtr head;
	char c;
	for (tc = 1; tc <= 10; ++tc) {
		cin >> len;
		/* init */
		head = NULL; added = 0;
		for (i = 0; i < len; ++i) {
			cin >> code[i];
			idx[i] = i;
		}

		cin >> N;
		for (i = 0; i < N; ++i) {
			cin >> c;
			if (c == INSERT) {
				cin >> x >> y;
				len += y;
				for (j = len - 1; j >= x + y; --j) idx[j] = idx[j - y];
				for (j = x; j < x + y; ++j) idx[j] = -1;
				// reindex
				reindex_node(head, x, y);
				// read data
				for (j = 0; j < y; ++j) {
					cin >> s;
					// insert node
					nodePtr nn = new_node(s, j + x, NULL);
					if (head == NULL) {
						head = nn;
					}
					else {
						nodePtr tmp, prev = new node();
						tmp = head, prev = NULL;
						while (tmp != NULL && tmp->idx < nn->idx) {
							prev = tmp;
							tmp = tmp->next;
						}
						if (prev == NULL) {
							head = nn;
						}
						else {
							prev->next = nn;
						}
						nn->next = tmp;
					}
				}
			}
			else if (c == DELETE) {
				cin >> x >> y;
				for (j = x; j < len - y; ++j) idx[j] = idx[j + y];
				for (j = len - y; j < len; ++j) idx[j] = -1;
				// delete node between index [x, x+y)
				delete_node(head, x, x + y);
				// reindex
				reindex_node(head, x + y, -y);
				len -= y;
			}
			else if (c == ADD) {
				cin >> y;
				for (j = len; j < len + y; ++j) idx[j] = -1;
				// read data
				for (j = 0; j < y; ++j) {
					cin >> s;
					// insert node
					nodePtr nn = new_node(s, j + len, NULL);
					if (head == NULL) {
						head = nn;
					}
					else {
						nodePtr tmp, prev = new node();
						tmp = head, prev = NULL;
						while (tmp != NULL && tmp->idx < nn->idx) {
							prev = tmp;
							tmp = tmp->next;
						}
						if (prev == NULL) {
							head = nn;
						}
						else {
							prev->next = nn;
						}
						nn->next = tmp;
					}
				} // for j
				len += y;
			}
		}
		cout << "#" << tc << " ";
		print_result(idx, code, head, 10);
		cout << '\n';
	}


	return 0;
}