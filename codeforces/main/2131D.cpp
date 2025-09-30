#include <bits/stdc++.h>

int problem2131D() {
    int n, u, v, ans = 0;
    std::cin >> n;
    std::vector<int> deg(n);
    std::vector<std::vector<int>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> u >> v;
        u--; v--;
        adj_list[u].push_back(v);   
        adj_list[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    if (n <= 3) return 0;

    // choose root as vertex i with max leaves with depth 1 (degree 1)
    int deg_1 = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) deg_1++;
    }
    int opt = 0;
    for (int i = 0; i < n; i++) {
        int curr = 0;
        for (int j: adj_list[i]) {
            if (deg[j] == 1) curr++;
        }
        opt = std::max(opt, curr);
    }
    ans = deg_1 - opt;
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