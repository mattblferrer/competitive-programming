#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;

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

void solve() {
    ll n, m, s, t, a, b, c;
    cin >> n >> m >> s >> t;
    vector<vector<pll>> adj_list(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        adj_list[a].push_back({c, b});
    }
    vector<ll> dist, path;
    dijkstra(s, adj_list, dist, path);
    if (dist[t] == INF) {
        cout << -1;
        return;
    }
    vector<ll> path_nodes;
    ll curr = t;
    while (curr != s) {
        path_nodes.push_back(curr);
        curr = path[curr];
    }
    path_nodes.push_back(s);
    reverse(path_nodes.begin(), path_nodes.end());
    cout << dist[t] << " " << path_nodes.size() - 1 << "\n";
    for (int i = 0; i < path_nodes.size() - 1; i++) {
        cout << path_nodes[i] << " " << path_nodes[i + 1] << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}