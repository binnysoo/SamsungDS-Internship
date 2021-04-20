void bfs(int v) {
	enQueue(v);

	while (!isEmpty()) {
		v = deQueue();

		if (visit[v] = false) {
			visit[v] = true;
			cout << v;
			for (int w = 1; w <= V; w++) {
				if (G[v][w] == 1 && visit[w] == false) {
					enQueue(w);
				}
			}
		}
	}
}

