#include <bits/stdc++.h>

void problem2126F() {
    int n, q, u, v, c, x;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    } 
    std::vector<std::vector<std::pair<int, int>>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> u >> v >> c;
        u--;
        v--;
        adj_list[u].push_back({v, c});
        adj_list[v].push_back({u, c});
    }
    // bfs to find first cost sum
    long long ans = 0;
    std::vector<bool> seen(n);
    seen[0] = true;
    std::queue<int> qu;
    qu.push(0);
    while (!qu.empty()) {
        int f = qu.front();
        qu.pop();
        for (auto pair: adj_list[f]) {
            v = pair.first;
            c = pair.second;
            if (seen[v]) continue;
            seen[v] = true;
            qu.push(v);
            if (a[f] != a[v]) ans += c;
        }
    }

    // query update cost sum
    for (int i = 0; i < q; i++) {
        std::cin >> u >> x;
        u--;
        for (auto pair: adj_list[u]) {
            v = pair.first;
            c = pair.second;
            if (a[u] == a[v] && a[v] != x) ans += c;
            if (a[u] != a[v] && a[v] == x) ans -= c;
        }
        a[u] = x;
        std::cout << ans << "\n";
    }

    // TODO: solve
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2126F();
    }
    return 0;
}