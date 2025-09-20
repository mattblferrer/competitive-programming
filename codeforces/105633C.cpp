#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = std::pair<long long, long long>;
const long long INF = 2e18;

void dijkstra(ll start, std::vector<std::vector<pll>> adj_list, 
    std::vector<ll>& dist, std::vector<ll>& path) {
    int n = adj_list.size();
    dist.resize(n, INF);
    path.resize(n, -1);
    std::priority_queue<pll, std::vector<pll>, std::greater<pll>> q;

    dist[start] = 0;  // starting vertex
    q.push({0, start});
    while (!q.empty()) {
        pll u = q.top();
        ll d_f = u.first;
        ll f = u.second;
        q.pop();

        if (d_f != dist[f]) continue;
        for (auto edge: adj_list[f]) {
            ll length = edge.first;
            ll v = edge.second;
            
            if (dist[f] + length < dist[v]) {
                dist[v] = dist[f] + length;
                path[v] = f;
                q.push({dist[v], v});
            }
        }
    }
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, u, v, q;
    cin >> n >> m;
    vector<int> p(n);
    vector<vector<pll>> adj_list(n);
    vector<ll> dist, path;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> q;
        u--; v--;
        adj_list[u].push_back({q, v});
        adj_list[v].push_back({q, u});
    }
    dijkstra(0, adj_list, dist, path);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dist[i] * p[i];
    }

    cout << ans;
    return 0;
}