#include <bits/stdc++.h>

int problem2131D() {
    int n, u, v, INF = INT_MAX, ans = 0;
    std::cin >> n;
    std::vector<std::set<int>> adj_list(n + 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> u >> v;
        adj_list[u].insert(v);
        adj_list[v].insert(u);
    }
    // bfs to find distances
    std::vector<int> dist(n + 1, INF);
    std::queue<int> q;
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (int v: adj_list[u]) {
            if (dist[v] != INF) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    // TODO: complete algorithm
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2131D() << "\n";
    }
    return 0;
}