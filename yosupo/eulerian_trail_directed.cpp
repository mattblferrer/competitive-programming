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

// Euler path/cycle in a directed graph as {vertices, edge ids}: edge ids[i] goes from vertices[i] to vertices[i + 1]
// so there are E + 1 vertices and E edge ids; both are empty if no Euler path exists, O(V + E)
pair<vector<int>, vector<int>> euler_directed(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    vector<int> in(n), out(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        out[u]++;
        in[v]++;
    }
    int start = -1, end = -1, any = -1;
    for (int u = 0; u < n; u++) {
        if (out[u] > 0 && any == -1) any = u;
        if (out[u] == in[u] + 1) {
            if (start != -1) return {};
            start = u;
        } else if (in[u] == out[u] + 1) {
            if (end != -1) return {};
            end = u;
        } else if (in[u] != out[u]) {
            return {};
        }
    }
    if (n == 0 || (start == -1) != (end == -1)) return {};
    if (start == -1) start = any == -1 ? 0 : any;
    vector<pair<int, int>> st{{start, -1}};  // {vertex, edge used to reach it}
    vector<int> verts, ids;
    while (!st.empty()) {
        int u = st.back().first;
        if (adj[u].empty()) {
            verts.push_back(u);
            if (st.back().second != -1) ids.push_back(st.back().second);
            st.pop_back();
        } else {
            st.push_back(adj[u].back());
            adj[u].pop_back();
        }
    }
    if ((int)ids.size() != m) return {};
    reverse(verts.begin(), verts.end());
    reverse(ids.begin(), ids.end());
    return {verts, ids};
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (ll i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    auto [verts, ids] = euler_directed(n, edges);
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
