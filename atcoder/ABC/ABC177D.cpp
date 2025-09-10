#include <bits/stdc++.h>

int ABC177D() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
        adj_list[b_i - 1].push_back(a_i - 1);
    }
    std::vector<bool> seen(n);
    int max_size = 0;

    for (int start = 0; start < n; start++) {
        if (seen[start]) continue;
        int ctr = 0;
        seen[start] = true;
        std::queue<int> q;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ctr++;
            for (int v: adj_list[u]) {
                if (seen[v]) continue;
                seen[v] = true;
                q.push(v);
            }
        }
        max_size = std::max(max_size, ctr);
    }
    return max_size;
}   

int main() { 
    std::cout << ABC177D();
    return 0;
}