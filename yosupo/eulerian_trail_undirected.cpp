// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// Euler path/cycle in an undirected graph as {vertices, edge ids}: edge ids[i] joins vertices[i] and vertices[i + 1]
// so there are E + 1 vertices and E edge ids; both are empty if no Euler path exists, O(V + E)
pair<vector<int>, vector<int>> euler_undirected(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }
    int start = -1, odd = 0;
    for (int u = 0; u < n; u++) {
        if (deg[u] > 0 && start == -1) start = u;
        if (deg[u] % 2) odd++;
    }
    for (int u = 0; u < n; u++) if (deg[u] % 2) start = u;  // a path must start at an odd-degree vertex
    if (n == 0 || (odd != 0 && odd != 2)) return {};
    if (start == -1) start = 0;
    vector<char> used(m, false);
    vector<pair<int, int>> st{{start, -1}};  // {vertex, edge used to reach it}
    vector<int> verts, ids;
    while (!st.empty()) {
        int u = st.back().first;
        while (!adj[u].empty() && used[adj[u].back().second]) adj[u].pop_back();
        if (adj[u].empty()) {
            verts.push_back(u);
            if (st.back().second != -1) ids.push_back(st.back().second);
            st.pop_back();
        } else {
            auto [v, id] = adj[u].back();
            used[id] = true;
            st.push_back({v, id});
        }
    }
    if ((int)ids.size() != m) return {};
    return {verts, ids};
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (ll i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    auto [verts, ids] = euler_undirected(n, edges);
    if (verts.empty()) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for (ll i = 0; i < verts.size(); i++) cout << verts[i] << " ";
    cout << "\n";
    for (ll i = 0; i < ids.size(); i++) cout << ids[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
