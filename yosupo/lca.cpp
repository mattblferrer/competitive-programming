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

// lowest common ancestor with O(1) queries (sparse table over DFS order), 0-indexed
//   LCA(adj, root)   preprocess the tree, O(n log n)
//   lca(u, v)        lowest common ancestor, O(1)
struct LCA {
    int n;
    vector<int> tin, order;
    vector<vector<int>> st;  // st[0][i] = tin of the parent of the vertex with tin i

    LCA(const vector<vector<int>> &adj, int root = 0): n(adj.size()), tin(n), order(n) {
        st.assign(1, vector<int>(n, 0));
        vector<pair<int, int>> stk{{root, root}};
        int t = 0;
        while (!stk.empty()) {
            auto [u, p] = stk.back();
            stk.pop_back();
            order[t] = u;
            st[0][t] = tin[p];
            tin[u] = t++;
            for (int v : adj[u]) if (v != p) stk.push_back({v, u});
        }
        for (int j = 1; (1 << j) <= n; j++) {
            st.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }

    int lca(int u, int v) const {
        if (u == v) return u;
        int l = tin[u], r = tin[v];
        if (l > r) swap(l, r);
        l++;
        r++;
        int k = __lg(r - l);
        return order[min(st[k][l], st[k][r - (1 << k)])];
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> p(n);
    vector<vector<int>> adj(n);
    for (ll i = 1; i < n; i++) {
        cin >> p[i];
        adj[p[i]].push_back(i);
        adj[i].push_back(p[i]);
    }
    LCA lca(adj, 0);
    for (ll i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v) << "\n";
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
