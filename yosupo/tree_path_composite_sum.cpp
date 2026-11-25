// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// answer of a tree DP for every choice of root; returns ans[v] for each v, O(n)
// s is a spec shaped like SumDist above: rerooting<SumDist>(adj) for static specs, rerooting(adj, s) to pass one
template <class S>
vector<typename S::T> rerooting(const vector<vector<int>> &adj, const S &s = S()) {
    using T = typename S::T;
    int n = adj.size();
    vector<int> order{0}, par(n, -1);
    for (int i = 0; i < (int)order.size(); i++) {
        for (int v : adj[order[i]]) {
            if (v == par[order[i]]) continue;
            par[v] = order[i];
            order.push_back(v);
        }
    }
    vector<T> down(n, s.id()), up(n, s.id()), ans(n);  // up[v] = what v's parent contributes to v
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        T cur = s.id();
        for (int u : adj[v]) if (u != par[v]) cur = s.merge(cur, s.lift(down[u], u, v));
        down[v] = s.finish(cur, v);
    }
    for (int v : order) {
        int k = adj[v].size();
        vector<T> pre(k + 1, s.id()), suf(k + 1, s.id());  // allows merge to have no inverse
        auto value = [&](int u) { return u == par[v] ? up[v] : s.lift(down[u], u, v); };
        for (int i = 0; i < k; i++) pre[i + 1] = s.merge(pre[i], value(adj[v][i]));
        for (int i = k - 1; i >= 0; i--) suf[i] = s.merge(value(adj[v][i]), suf[i + 1]);
        ans[v] = s.finish(pre[k], v);
        for (int i = 0; i < k; i++) {
            int u = adj[v][i];
            if (u != par[v]) up[u] = s.lift(s.finish(s.merge(pre[i], suf[i + 1]), v), v, u);
        }
    }
    return ans;
}

// rerooting example: each edge e is a map f_e(x) = b x + c mod `mod` and each vertex v has a value a[v];
// for every x, the sum over all y of f along the path from x to y applied to a[y] (the edge nearest y first)
// T = {sum of the values reaching this side's top vertex, number of vertices on this side}
struct PathComposite {
    using T = pll;
    ll mod = 998'244'353;
    vector<ll> val;
    map<pair<int, int>, pll> edge;  // {b, c} of each edge, keyed by its endpoints {min, max}

    T id() const { return {0, 0}; }
    T merge(const T &a, const T &b) const { return {(a.first + b.first) % mod, a.second + b.second}; }
    T lift(const T &x, int from, int to) const {
        auto [b, c] = edge.at({min(from, to), max(from, to)});
        return {(b * x.first + c * x.second) % mod, x.second};
    }
    T finish(const T &x, int v) const { return {(x.first + val[v]) % mod, x.second + 1}; }
};

void solve() {
    ll n;
    cin >> n;
    PathComposite pc;
    pc.val.resize(n);
    for (ll i = 0; i < n; i++) cin >> pc.val[i];
    vector<vector<int>> adj(n);
    for (ll i = 0; i < n - 1; i++) {
        ll u, v, b, c;
        cin >> u >> v >> b >> c;
        adj[u].push_back(v);
        adj[v].push_back(u);
        pc.edge[{min(u, v), max(u, v)}] = {b, c};
    }
    vector<pll> ans = rerooting(adj, pc);
    for (ll i = 0; i < n; i++) cout << ans[i].first << " ";
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
