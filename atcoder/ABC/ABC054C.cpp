#include <bits/stdc++.h>

int n, m, a_i, b_i;
int dfs(std::vector<std::vector<int>>& adj_list, std::vector<bool> seen, 
    int depth, int u) {
    seen[u] = true;
    if (depth == n - 1) {
        bool all_true = true;
        for (bool b: seen) {
            if (b == false) all_true = false;
        }
        if (all_true) return 1;
        else return 0;
    }
    int ans = 0;
    for (int v: adj_list[u]) {
        ans += dfs(adj_list, seen, depth + 1, v);
    }
    return ans;
}

int ABC054C() {
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        a_i--;
        b_i--;
        adj_list[a_i].push_back(b_i);
        adj_list[b_i].push_back(a_i);
    }
    std::vector<bool> seen(n);
    return dfs(adj_list, seen, 0, 0);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC054C() << "\n";
    return 0;
}