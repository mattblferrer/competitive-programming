#include <bits/stdc++.h>

void dfs(std::vector<std::vector<int>>& adj_list, std::vector<bool>& seen, 
    std::deque<int>& order, int u) {
    if (seen[u]) return;
    for (int v: adj_list[u]) {
        dfs(adj_list, seen, order, v);
    }
    seen[u] = true;
    order.push_front(u);
}

int DP_G() {
    int n, m, x_i, y_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n), inc_list(n);
    std::deque<int> order;
    std::vector<bool> seen(n);
    for (int i = 0; i < m; i++) {
        std::cin >> x_i >> y_i;
        adj_list[x_i - 1].push_back(y_i - 1);
        inc_list[y_i - 1].push_back(x_i - 1);
    }
    for (int i = 0; i < n; i++) {
        dfs(adj_list, seen, order, i);
    }

    std::vector<int> lp(n);
    for (int y_i: order) {
        for (int x_i: inc_list[y_i]) {
            lp[y_i] = std::max(1 + lp[x_i], lp[y_i]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = std::max(ans, lp[i]);
    }
    return ans;
}

int main() {
    std::cout << DP_G();
    return 0;
}