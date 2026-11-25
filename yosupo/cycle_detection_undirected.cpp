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

// some cycle of an undirected multigraph as {vertices v_0..v_{L-1}, edge ids e_0..e_{L-1}}, where e_i joins v_i and
// v_{i+1} (and e_{L-1} joins v_{L-1} and v_0); a self-loop is a cycle of length 1 and two parallel edges one of
// length 2; both empty if the graph is a forest. Iterative DFS that skips only the edge it came in by, O(V + E)
pair<vector<int>, vector<int>> undirected_cycle(int n, const vector<pair<int, int>> &edges) {
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    for (int i = 0; i < (int)edges.size(); i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        if (u != v) adj[v].push_back({u, i});
    }
    vector<int> state(n, 0), par(n, -1), in_edge(n, -1), next(n, 0);
    for (int s = 0; s < n; s++) {
        if (state[s]) continue;
        vector<int> st{s};
        state[s] = 1;
        while (!st.empty()) {
            int u = st.back();
            if (next[u] == (int)adj[u].size()) {
                state[u] = 2;
                st.pop_back();
                continue;
            }
            auto [v, id] = adj[u][next[u]++];
            if (id == in_edge[u]) continue;
            if (state[v] == 0) {
                state[v] = 1;
                par[v] = u;
                in_edge[v] = id;
                st.push_back(v);
            } else if (state[v] == 1) {  // v is an ancestor of u (or u itself): v -> ... -> u by tree edges, then u - v
                vector<int> vs, es;
                for (int x = u; x != v; x = par[x]) {
                    vs.push_back(x);
                    es.push_back(in_edge[x]);
                }
                vs.push_back(v);
                reverse(vs.begin(), vs.end());
                reverse(es.begin(), es.end());
                es.push_back(id);
                return {vs, es};
            }
        }
    }
    return {};
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (ll i = 0; i < m; i++) cin >> edges[i].first >> edges[i].second;
    auto [vs, es] = undirected_cycle(n, edges);
    if (vs.empty()) {
        cout << -1 << "\n";
        return;
    }
    cout << vs.size() << "\n";
    for (ll i = 0; i < vs.size(); i++) cout << vs[i] << " ";
    cout << "\n";
    for (ll i = 0; i < es.size(); i++) cout << es[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
