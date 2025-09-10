#include <bits/stdc++.h>

void ABC168D() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n, std::vector<int>());
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
        adj_list[b_i - 1].push_back(a_i - 1);
    }
    std::vector<int> signs(n);
    std::queue<int> q;
    std::vector<bool> seen(n);
    q.push(0);
    seen[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: adj_list[u]) {
            if (seen[v]) continue;
            seen[v] = true;
            signs[v] = u;
            q.push(v);
        }
    }

    bool way = true;
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            way = false;
            break;
        }
    }
    if (!way) {
        std::cout << "No\n";
        return;
    }
    else {
        std::cout << "Yes\n";
    }
    for (int i = 1; i < n; i++) {   
        std::cout << signs[i] + 1 << "\n";
    }
}

int main() {
    ABC168D();
    return 0;
}