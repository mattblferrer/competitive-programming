#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

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
    ll n, m, y;
    cin >> n >> m >> y;
    vector<vector<pll>> adj(n + 3);
    for (ll i = 1; i <= m; i++) {
        ll ui, vi, ti;
        cin >> ui >> vi >> ti;
        adj[ui].push_back({ti, vi});
        adj[vi].push_back({ti, ui});
    }

    adj[n + 1].push_back({y, n + 2});
    vector<ll> x(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> x[i];
        adj[i].push_back({x[i], n + 1});
        adj[n + 2].push_back({x[i], i});
    }

    dijkstra djk(1, adj);
    djk.run();
    for (ll i = 2; i <= n; i++) cout << djk.dist[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}