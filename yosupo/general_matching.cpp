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

// maximum matching in a general graph (Edmonds' blossom)
// after run: match[v] = partner of v, -1 if unmatched
//   Blossom(n)          empty graph on n vertices, O(n)
//   add_edge(u, v)      add the undirected edge u - v (self-loops are ignored), O(1)
//   lca(a, b)           base of the blossom formed by the alternating paths from a and b, O(V)
//   mark_path(v, b, c)  mark the blossom vertices on the path from v up to base b, O(V)
//   find_path(root)     BFS for an augmenting path from root, returns its end or -1, O(V^2)
//   run()               size of the maximum matching, O(V^3)
struct Blossom {
    int n;
    vector<vector<int>> adj;
    vector<int> match, par, base;
    vector<char> used, in_blossom;

    Blossom(int n = 0): n(n), adj(n), match(n, -1), par(n), base(n), used(n), in_blossom(n) {}

    void add_edge(int u, int v) {
        if (u == v) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int lca(int a, int b) {
        vector<char> seen(n, false);
        while (true) {
            a = base[a];
            seen[a] = true;
            if (match[a] == -1) break;
            a = par[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            b = par[match[b]];
        }
    }

    void mark_path(int v, int b, int child) {
        while (base[v] != b) {
            in_blossom[base[v]] = in_blossom[base[match[v]]] = true;
            par[v] = child;
            child = match[v];
            v = par[match[v]];
        }
    }

    int find_path(int root) {
        fill(used.begin(), used.end(), false);
        fill(par.begin(), par.end(), -1);
        iota(base.begin(), base.end(), 0);
        queue<int> q;
        q.push(root);
        used[root] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : adj[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && par[match[to]] != -1)) {
                    int cur = lca(v, to);
                    fill(in_blossom.begin(), in_blossom.end(), false);
                    mark_path(v, cur, to);
                    mark_path(to, cur, v);
                    for (int i = 0; i < n; i++) {
                        if (in_blossom[base[i]]) {
                            base[i] = cur;
                            if (!used[i]) {
                                used[i] = true;
                                q.push(i);
                            }
                        }
                    }
                }
                else if (par[to] == -1) {
                    par[to] = v;
                    if (match[to] == -1) return to;
                    used[match[to]] = true;
                    q.push(match[to]);
                }
            }
        }
        return -1;
    }

    int run() {
        int res = 0;
        for (int v = 0; v < n; v++) {
            if (match[v] != -1) continue;
            int u = find_path(v);
            if (u != -1) res++;
            while (u != -1) {
                int pv = par[u], next = match[pv];
                match[u] = pv;
                match[pv] = u;
                u = next;
            }
        }
        return res;
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;
    Blossom b(n);
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        b.add_edge(u, v);
    }
    ll sz = b.run();
    cout << sz << "\n";
    for (ll i = 0; i < n; i++) {
        if (i < b.match[i]) cout << i << " " << b.match[i] << "\n";
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
