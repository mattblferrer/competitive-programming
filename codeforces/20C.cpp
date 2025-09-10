#include <bits/stdc++.h>

void problem20C() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long inf = 999999999999999;
    int n, m, a_i, b_i, w_i;
    std::cin >> n >> m;
    std::vector<long long> dist(n, inf);
    std::vector<long long> path(n, -1);
    std::vector<std::vector<std::pair<long long, long long>>> adj_list(n);
    std::priority_queue<std::pair<long long, long long>, 
        std::vector<std::pair<long long, long long>>, 
        std::greater<std::pair<long long, long long>>> q;

    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i >> w_i;
        adj_list[a_i - 1].push_back({w_i, b_i - 1});
        adj_list[b_i - 1].push_back({w_i, a_i - 1});
    }

    dist[0] = 0;  // starting vertex
    q.push({0, 0});
    while (!q.empty()) {
        std::pair<long long, long long> u = q.top();
        long long d_f = u.first;
        long long f = u.second;
        q.pop();

        if (d_f != dist[f]) continue;
        for (auto edge: adj_list[f]) {
            long long length = edge.first;
            long long v = edge.second;
            
            if (dist[f] + length < dist[v]) {
                dist[v] = dist[f] + length;
                path[v] = f;
                q.push({dist[v], v});
            }
            if (v == n - 1) {
                break;
            }
        }
    }
    if (dist[n - 1] == inf) {
        std::cout << -1;
        return;
    }

    int curr = n - 1;
    std::deque<int> shortest;
    do {
        shortest.push_front(curr + 1);
        curr = path[curr];
    } while (curr != 0);
    std::cout << "1 ";  // starting vertex
    for (int v: shortest) {
        std::cout << v << " ";
    }
}

int main() {
    problem20C();
    return 0;
}