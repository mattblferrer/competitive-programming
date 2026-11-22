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

// dominator tree of a directed graph from root (Lengauer-Tarjan), O(E log V)
// returns idom where idom[v] = immediate dominator of v, idom[root] = root, idom[v] = -1 if v is unreachable
vector<int> dominator_tree(const vector<vector<int>> &adj, int root) {
    int n = adj.size();
    vector<int> dfn(n, -1), order, par_dfn;  // the rest of the algorithm works on DFS numbers
    vector<pair<int, int>> stk{{root, -1}};
    while (!stk.empty()) {
        auto [u, p] = stk.back();
        stk.pop_back();
        if (dfn[u] != -1) continue;
        dfn[u] = order.size();
        order.push_back(u);
        par_dfn.push_back(p);
        for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
            if (dfn[adj[u][i]] == -1) stk.push_back({adj[u][i], dfn[u]});
        }
    }
    int k = order.size();
    vector<vector<int>> pred(k), bucket(k);
    for (int i = 0; i < k; i++) {
        for (int v : adj[order[i]]) if (dfn[v] != -1) pred[dfn[v]].push_back(i);
    }
    vector<int> semi(k), idom_dfn(k, 0), label(k), anc(k, -1), compress_path;
    iota(semi.begin(), semi.end(), 0);
    iota(label.begin(), label.end(), 0);
    auto eval = [&](int v) {
        if (anc[v] == -1) return label[v];
        compress_path.clear();
        for (int u = v; anc[anc[u]] != -1; u = anc[u]) compress_path.push_back(u);
        for (int i = (int)compress_path.size() - 1; i >= 0; i--) {
            int x = compress_path[i];
            if (semi[label[anc[x]]] < semi[label[x]]) label[x] = label[anc[x]];
            anc[x] = anc[anc[x]];
        }
        return label[v];
        };
    for (int w = k - 1; w >= 1; w--) {
        for (int v : pred[w]) semi[w] = min(semi[w], semi[eval(v)]);
        bucket[semi[w]].push_back(w);
        anc[w] = par_dfn[w];
        for (int v : bucket[par_dfn[w]]) {
            int u = eval(v);
            idom_dfn[v] = semi[u] < semi[v] ? u : par_dfn[w];
        }
        bucket[par_dfn[w]].clear();
    }
    for (int w = 1; w < k; w++) {
        if (idom_dfn[w] != semi[w]) idom_dfn[w] = idom_dfn[idom_dfn[w]];
    }
    vector<int> idom(n, -1);
    for (int i = 0; i < k; i++) idom[order[i]] = order[idom_dfn[i]];
    return idom;
}

void solve() {
    ll n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> adj(n);
    for (ll i = 0; i < m; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        adj[ai].push_back(bi);
    }
    vector<int> p = dominator_tree(adj, s);
    for (ll i = 0; i < n; i++) cout << p[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
