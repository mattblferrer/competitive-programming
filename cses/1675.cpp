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

// disjoint set union with path compression and union by size
//   DSU(n)               n singleton sets {0}, ..., {n - 1}, O(n)
//   find_set(a)          representative of a's set, O(alpha(n)) amortized
//   union_sets(a, b)     merge the sets of a and b; false if already in the same set, O(alpha(n))
//   is_connected(a, b)   whether a and b are in the same set, O(alpha(n))
struct DSU {
    vector<int> parent, sz;

    DSU(int n): parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find_set(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find_set(parent[a]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool is_connected(int a, int b) { return find_set(a) == find_set(b); }
};

// minimum spanning forest (Kruskal), edges are {w, u, v}; returns {total weight, indices of the chosen edges},
// O(E log E)
pair<ll, vector<int>> kruskal(int n, const vector<array<ll, 3>> &edges) {
    vector<int> p(n), order(edges.size()), chosen;
    iota(p.begin(), p.end(), 0);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return edges[a] < edges[b]; });
    auto find_set = [&](int x) {  // path halving, no recursion
        while (p[x] != x) x = p[x] = p[p[x]];
        return x;
        };
    ll total = 0;
    for (int i : order) {
        int u = find_set(edges[i][1]), v = find_set(edges[i][2]);
        if (u == v) continue;
        p[u] = v;
        total += edges[i][0];
        chosen.push_back(i);
    }
    return {total, chosen};
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<array<ll, 3>> edges(m);
    DSU dsu(n);
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        edges[i] = {c, a, b};
        dsu.union_sets(a, b);
    }
    set<ll> pars;
    for (ll i = 0; i < n; i++) pars.insert(dsu.find_set(i));
    if (pars.size() != 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    pair<ll, vector<int>> mst = kruskal(n, edges);
    cout << mst.first << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
