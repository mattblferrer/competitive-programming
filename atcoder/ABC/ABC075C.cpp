#include <bits/stdc++.h>

int ABC075C() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        edges[i] = {a_i - 1, b_i - 1};
    }
    int bridges = 0;
    for (int i = 0; i < m; i++) {
        std::vector<std::vector<int>> adj_list(n);
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            adj_list[edges[j].first].push_back(edges[j].second);
            adj_list[edges[j].second].push_back(edges[j].first);
        }
        std::vector<bool> seen(n);
        seen[0] = true;
        std::queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj_list[u]) {
                if (seen[v]) continue;
                q.push(v);
                seen[v] = true;
            }
        }
        for (int k = 0; k < n; k++) {
            if (!seen[k]) {
                bridges++;
                break;
            }
        }
    }
    return bridges;
}

int main() {
    std::cout << ABC075C();
    return 0;
}