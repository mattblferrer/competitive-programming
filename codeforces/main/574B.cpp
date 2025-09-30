#include <bits/stdc++.h>

int problem574B() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n);
    std::vector<std::vector<bool>> adj_mat(n, std::vector<bool>(n));
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
        adj_list[b_i - 1].push_back(a_i - 1);
        adj_mat[a_i - 1][b_i - 1] = true;
        adj_mat[b_i - 1][a_i - 1] = true;
    }
    std::vector<int> neighbors(n);
    for (int i = 0; i < n; i++) {
        neighbors[i] = adj_list[i].size();
    }
    std::vector<bool> seen(n);
    int min_r = 99999;
    for (int start = 0; start < n; start++) {
        if (seen[start]) continue;
        std::queue<int> q;
        q.push(start);
        seen[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj_list[u]) {
                for (int i = 0; i < n; i++) {
                    if (adj_mat[u][i] && adj_mat[v][i]) {
                        min_r = std::min(min_r, neighbors[u] + neighbors[v] + 
                            neighbors[i] - 6);
                    }
                }
                if (seen[v]) continue;
                q.push(v);
                seen[v] = true;
            }
        }
    }
    if (min_r == 99999) return -1;
    return min_r;
}

int main() {
    std::cout << problem574B();
    return 0;
}