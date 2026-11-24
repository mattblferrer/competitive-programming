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

// binary lifting on a rooted tree, 0-indexed
//   BinaryLift(adj, root)   preprocess the tree, O(n log n)
//   kth_ancestor(u, k)      k-th ancestor of u, -1 if it doesn't exist, O(log n)
//   is_ancestor(a, u)       true if a is an ancestor of u (or a == u), O(log n)
//   lca(u, v)               lowest common ancestor, O(log n)
struct BinaryLift {
    int n, lg;
    vector<int> dep;
    vector<vector<int>> up;

    BinaryLift(const vector<vector<int>> &adj, int root = 0): n(adj.size()), lg(1), dep(n, 0) {
        while ((1 << lg) < n) lg++;
        up.assign(lg, vector<int>(n, root));
        vector<int> st{root};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : adj[u]) {
                if (v == up[0][u]) continue;
                up[0][v] = u;
                dep[v] = dep[u] + 1;
                st.push_back(v);
            }
        }
        for (int k = 1; k < lg; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }

    int kth_ancestor(int u, int k) const {
        if (k > dep[u]) return -1;
        for (int i = 0; i < lg; i++) if (k >> i & 1) u = up[i][u];
        return u;
    }

    bool is_ancestor(int a, int u) const { return dep[a] <= dep[u] && kth_ancestor(u, dep[u] - dep[a]) == a; }

    int lca(int u, int v) const {
        if (dep[u] < dep[v]) swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int k = lg - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    BinaryLift bl(adj);
    for (ll i = 0; i < q; i++) {
        ll s, t, k;
        cin >> s >> t >> k;
        ll l = bl.lca(s, t);
        ll ds = bl.dep[s] - bl.dep[l], d = ds + bl.dep[t] - bl.dep[l];
        if (k > d) cout << -1 << "\n";
        else if (k <= ds) cout << bl.kth_ancestor(s, k) << "\n";
        else cout << bl.kth_ancestor(t, d - k) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
