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

// edge ids of some directed cycle, in order (edge i goes u -> v for edges[i] = {u, v}), empty if the graph is acyclic
// iterative DFS: an edge to a vertex still on the DFS stack closes a cycle, O(V + E)
vector<int> directed_cycle(int n, const vector<pair<int, int>> &edges) {
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    for (int i = 0; i < (int)edges.size(); i++) adj[edges[i].first].push_back({edges[i].second, i});
    vector<int> state(n, 0), in_edge(n, -1), next(n, 0);  // state: 0 unseen, 1 on the stack, 2 done
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
            if (state[v] == 0) {
                state[v] = 1;
                in_edge[v] = id;
                st.push_back(v);
            } else if (state[v] == 1) {  // v -> ... -> u by tree edges, then u -> v
                vector<int> cyc{id};
                for (int x = u; x != v; x = edges[in_edge[x]].first) cyc.push_back(in_edge[x]);
                reverse(cyc.begin(), cyc.end());
                return cyc;
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
    vector<int> cyc = directed_cycle(n, edges);
    if (cyc.empty()) {
        cout << -1 << "\n";
        return;
    }
    cout << cyc.size() << "\n";
    for (ll i = 0; i < cyc.size(); i++) cout << cyc[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
