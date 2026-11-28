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

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<pll>> adj(n + 1);
    map<ll, vector<pll>> edges;
    for (ll i = 0; i < m; i++) {
        ll ui, vi, ci;
        cin >> ui >> vi >> ci;
        adj[ui].push_back({vi, ci});
        adj[vi].push_back({ui, ci});
        edges[ci].push_back({ui, vi});
    }
    vector<ll> dp(n + 1);
    for (auto &[ci, vec] : edges) {
        map<ll, ll> upd;
        for (auto &[u, v] : vec) {
            upd[v] = max(upd[v], dp[u] + ci);
            upd[u] = max(upd[u], dp[v] + ci);
        }
        for (auto &[u, val] : upd) {
            dp[u] = max(dp[u], val);
        }
    }
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
