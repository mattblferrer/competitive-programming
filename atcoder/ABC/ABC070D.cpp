#include <bits/stdc++.h>

void ABC070D() {
    long long n, a_i, b_i, c_i, q, k, x_i, y_i;
    long long INF = 100000000000000000;
    std::cin >> n;
    std::vector<std::vector<std::pair<long long, long long>>> adj_list(n);
    for (int i = 1; i < n; i++) {
        std::cin >> a_i >> b_i >> c_i;
        adj_list[a_i - 1].push_back({b_i - 1, c_i});
        adj_list[b_i - 1].push_back({a_i - 1, c_i});
    }
    std::cin >> q >> k;
    std::vector<long long> dist(n, INF);
    dist[k - 1] = 0;
    std::queue<long long> pq;
    pq.push(k - 1);
    
    while (!pq.empty()) {
        long long u = pq.front();
        pq.pop();
        for (auto v: adj_list[u]) {
            long long b = v.first;
            long long c = v.second;
            if (dist[b] == INF) {
                dist[b] = dist[u] + c;
                pq.push(b);
            }
        }
    }
    
    for (int i = 0; i < q; i++) {
        std::cin >> x_i >> y_i;
        std::cout << dist[x_i - 1] + dist[y_i - 1] << "\n";
    } 
}

int main() {
    ABC070D();
    return 0;
}