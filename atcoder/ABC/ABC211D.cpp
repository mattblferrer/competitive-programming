#include <bits/stdc++.h>

long long ABC211D() {
    long long n, m, a_i, b_i;
    long long mod = pow(10, 9) + 7;
    std::cin >> n >> m;
    std::vector<std::vector<long long>> adj_list(n);
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
        adj_list[b_i - 1].push_back(a_i - 1);
    }
    std::vector<long long> dist(n, n + 1);
    std::vector<long long> paths(n);
    paths[0] = 1;
    std::queue<long long> q;
    q.push(0);
    while (!q.empty()) {
        long long u = q.front();
        q.pop();
        for (long long v: adj_list[u]) {
            if (dist[v] != n + 1) {
                if (dist[v] == dist[u] + 1) {
                    paths[v] = (paths[v] + paths[u]) % mod;
                }
                continue;
            }
            dist[v] = dist[u] + 1;
            paths[v] = paths[u];
            q.push(v);
        }
    }
    return paths[n - 1];
}   

int main() { 
    std::cout << ABC211D();
    return 0;
}