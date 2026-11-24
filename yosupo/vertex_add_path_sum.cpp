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

// heavy-light decomposition, 0-indexed; maps paths and subtrees to ranges of pos[] for a segment tree on [l, r)
//   HLD(adj, root)              preprocess the tree, O(n)
//   lca(u, v)                   lowest common ancestor, O(log n)
//   path(u, v, f, skip_lca)     call f(l, r) or f(l, r, up) for each range on the path u - v, in order from u to v;
//                               up means the path walks the range from r - 1 down to l (for non-commutative ops);
//                               skip_lca leaves out the lca (for edge values), O(log n) calls
//   subtree(u)                  range {l, r} of the subtree of u, O(1)
struct HLD {
    int n;
    vector<int> par, dep, sz, heavy, head, pos;

    HLD(const vector<vector<int>> &adj, int root = 0)
        : n(adj.size()), par(n, -1), dep(n, 0), sz(n, 1), heavy(n, -1), head(n, root), pos(n, 0) {
        vector<int> order{root};
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == par[u]) continue;
                par[v] = u;
                dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i], p = par[u];
            sz[p] += sz[u];
            if (heavy[p] == -1 || sz[u] > sz[heavy[p]]) heavy[p] = u;
        }
        for (int u : order) {  // the heavy child comes first, so each chain and each subtree is contiguous
            int next = pos[u] + 1;
            if (heavy[u] != -1) {
                head[heavy[u]] = head[u];
                pos[heavy[u]] = next;
                next += sz[heavy[u]];
            }
            for (int v : adj[u]) {
                if (v == par[u] || v == heavy[u]) continue;
                head[v] = v;
                pos[v] = next;
                next += sz[v];
            }
        }
    }

    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            v = par[head[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    template <class F>
    void path(int u, int v, F f, bool skip_lca = false) const {
        auto call = [&](int l, int r, bool up) {
            if constexpr (is_invocable_v<F, int, int, bool>) f(l, r, up);
            else f(l, r);
        };
        vector<pair<int, int>> down;  // ranges on the v side, called last in reverse
        while (head[u] != head[v]) {
            if (dep[head[u]] >= dep[head[v]]) {
                call(pos[head[u]], pos[u] + 1, true);
                u = par[head[u]];
            } else {
                down.push_back({pos[head[v]], pos[v] + 1});
                v = par[head[v]];
            }
        }
        if (dep[u] >= dep[v]) {
            if (pos[v] + skip_lca < pos[u] + 1) call(pos[v] + skip_lca, pos[u] + 1, true);
        } else if (pos[u] + skip_lca < pos[v] + 1) {
            call(pos[u] + skip_lca, pos[v] + 1, false);
        }
        for (int i = (int)down.size() - 1; i >= 0; i--) call(down[i].first, down[i].second, false);
    }

    pair<int, int> subtree(int u) const { return {pos[u], pos[u] + sz[u]}; }
};

// Fenwick tree (0-indexed)
//   Fenwick(n)          n zeros, O(n)
//   Fenwick(a)           build from a, O(n)
//   add(i, v)            a[i] += v, O(log n)
//   sum(r)               sum of a[0..r), O(log n)
//   sum(l, r)            sum of a[l..r), O(log n)
//   get(i)               a[i], O(log n)
//   set(i, v)            a[i] = v, O(log n)
//   lower_bound(s)       smallest p with sum(p + 1) >= s, n if none; requires a[i] >= 0, O(log n)
struct Fenwick {
    int n;
    vector<ll> t;

    Fenwick(int n = 0): n(n), t(n + 1, 0) {}

    Fenwick(const vector<ll> &a): Fenwick((int)a.size()) {
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }

    void add(int i, ll v) {
        for (i++; i <= n; i += i & -i) t[i] += v;
    }

    ll sum(int r) const {
        ll res = 0;
        for (; r > 0; r -= r & -r) res += t[r];
        return res;
    }

    ll sum(int l, int r) const { return sum(r) - sum(l); }

    ll get(int i) const { return sum(i, i + 1); }

    void set(int i, ll v) { add(i, v - get(i)); }

    int lower_bound(ll s) const {
        int p = 0;
        for (int k = n ? __lg(n) : 0; k >= 0 && n; k--) {
            if (p + (1 << k) <= n && t[p + (1 << k)] < s) {
                p += 1 << k;
                s -= t[p];
            }
        }
        return p;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> adj(n);
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    HLD hld(adj);
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) b[hld.pos[i]] = a[i];
    Fenwick fen(b);
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll p, x;
            cin >> p >> x;
            fen.add(hld.pos[p], x);
        }
        else if (t == 1) {
            ll u, v;
            cin >> u >> v;
            ll res = 0;
            hld.path(u, v, [&](int l, int r) { res += fen.sum(l, r); });
            cout << res << "\n";
        }
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
