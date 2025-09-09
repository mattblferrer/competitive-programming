#include <bits/stdc++.h>

void problem689B() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), m(n, 999999);
    std::vector<std::vector<int>> adj_list(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;  // 0-index
        adj_list[i].push_back(a[i]);
        if (i != n) adj_list[i].push_back(i + 1);
        if (i != 0) adj_list[i].push_back(i - 1);
    }

    std::queue<int> q;
    q.push(0);
    m[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: adj_list[u]) {
            if (m[v] != 999999) continue;
            m[v] = m[u] + 1;
            q.push(v);
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << m[i] << " ";
    }
}

int main() {
    problem689B();	
    return 0;
}