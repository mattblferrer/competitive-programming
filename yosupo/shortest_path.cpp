#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;

const long long INF = 2e18;

struct dijkstra {
    ll start, size;
    vector<vector<pll>> adj_list;
    vector<ll> dist, path;

    dijkstra(ll start, vector<vector<pll>> adj_list) {
        this->start = start;
        this->adj_list = adj_list;
        this->size = adj_list.size();
        dist.resize(size, INF);
        path.resize(size, -1);
    }

    void run() {
        priority_queue<pll, vector<pll>, greater<pll>> q;
        dist[start] = 0;  // starting vertex
        q.push({0, start});
        while (!q.empty()) {
            pll u = q.top();
            ll d_f = u.first;
            ll f = u.second;
            q.pop();

            if (d_f != dist[f]) continue;
            for (auto edge : adj_list[f]) {
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

    bool has_path(ll end) {
        return !(dist[end] >= INF);
    }
};

void solve() {
    ll n, m, s, t, a, b, c;
    cin >> n >> m >> s >> t;
    vector<vector<pll>> adj_list(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        adj_list[a].push_back({c, b});
    }
    dijkstra djk(s, adj_list);
    djk.run();
    if (!djk.has_path(t)) {
        cout << -1;
        return;
    }

    vector<ll> path_nodes;
    ll curr = t;
    while (curr != s) {
        path_nodes.push_back(curr);
        curr = djk.path[curr];
    }
    path_nodes.push_back(s);
    reverse(path_nodes.begin(), path_nodes.end());
    cout << djk.dist[t] << " " << path_nodes.size() - 1 << "\n";
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