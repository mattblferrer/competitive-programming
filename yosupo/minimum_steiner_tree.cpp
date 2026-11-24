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

// cheapest connected subgraph containing all terminals (Steiner tree): returns {total weight, edge ids}, {INF, {}} if impossible
// edges are {u, v, w} with w >= 0; k = number of terminals, O(3^k V + 2^k E log V)
pair<ll, vector<int>> steiner_tree(int n, const vector<array<ll, 3>> &edges, const vector<int> &terminals) {
    int k = terminals.size();
    if (k == 0) return {0, {}};
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    for (int i = 0; i < (int)edges.size(); i++) {
        adj[edges[i][0]].push_back({(int)edges[i][1], i});
        adj[edges[i][1]].push_back({(int)edges[i][0], i});
    }
    // dp[mask][v] = cheapest tree containing mask and v; it came from edge via[mask][v] if >= 0,
    // else from the split sub[mask][v] if > 0, else it is a terminal on its own
    vector<vector<ll>> dp(1 << k, vector<ll>(n, INF));
    vector<vector<int>> via(1 << k, vector<int>(n, -1)), sub(1 << k, vector<int>(n, 0));
    for (int i = 0; i < k; i++) dp[1 << i][terminals[i]] = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        vector<ll> &d = dp[mask];
        for (int s = (mask - 1) & mask; s; s = (s - 1) & mask) {
            if (s < (mask ^ s)) continue;  // each split only needs trying once
            for (int v = 0; v < n; v++) {
                if (dp[s][v] < INF && dp[mask ^ s][v] < INF && dp[s][v] + dp[mask ^ s][v] < d[v]) {
                    d[v] = dp[s][v] + dp[mask ^ s][v];
                    sub[mask][v] = s;
                }
            }
        }
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        for (int v = 0; v < n; v++) if (d[v] < INF) pq.push({d[v], v});
        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();
            if (cost != d[u]) continue;
            for (auto [v, id] : adj[u]) {
                if (cost + edges[id][2] < d[v]) {
                    d[v] = cost + edges[id][2];
                    via[mask][v] = id;
                    pq.push({d[v], v});
                }
            }
        }
    }
    int full = (1 << k) - 1;
    if (dp[full][terminals[0]] == INF) return {INF, {}};
    vector<int> used;
    vector<pair<int, int>> st{{full, terminals[0]}};
    while (!st.empty()) {
        auto [mask, v] = st.back();
        st.pop_back();
        if (int id = via[mask][v]; id >= 0) {
            used.push_back(id);
            st.push_back({mask, int(edges[id][0] ^ edges[id][1] ^ v)});
        } else if (int s = sub[mask][v]) {
            st.push_back({s, v});
            st.push_back({mask ^ s, v});
        }
    }
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());  // only zero-weight edges can repeat
    return {dp[full][terminals[0]], used};
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<array<ll, 3>> edges(m);
    for (ll i = 0; i < m; i++) cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    ll k;
    cin >> k;
    vector<int> terminals(k);
    for (ll i = 0; i < k; i++) cin >> terminals[i];
    auto [cost, ids] = steiner_tree(n, edges, terminals);
    cout << cost << " " << ids.size() << "\n";
    for (ll i = 0; i < ids.size(); i++) cout << ids[i] << " ";
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
