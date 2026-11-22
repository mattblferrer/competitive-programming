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

// maximum bipartite matching (Hopcroft-Karp); left vertices 0..n-1, right vertices 0..m-1
// after max_matching: l[u] = right match of u, r[v] = left match of v, -1 if unmatched
//   HopcroftKarp(n, m)    empty graph, O(n + m)
//   add_edge(u, v)        add the edge from left u to right v, O(1)
//   bfs()                 build the layers; true if an augmenting path exists, O(V + E)
//   dfs(u)                try to augment from left u along the layers, O(V + E) per phase
//   max_matching()        size of the maximum matching, O(E sqrt V)
//   min_vertex_cover()    minimum vertex cover as {left vertices, right vertices} (Konig); call max_matching first, O(V + E)
struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> l, r, dist;

    HopcroftKarp(int n = 0, int m = 0): n(n), m(m), adj(n), l(n, -1), r(m, -1), dist(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            dist[u] = l[u] == -1 ? 0 : -1;
            if (l[u] == -1) q.push(u);
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (r[v] == -1) found = true;
                else if (dist[r[v]] == -1) {
                    dist[r[v]] = dist[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (r[v] == -1 || (dist[r[v]] == dist[u] + 1 && dfs(r[v]))) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs()) {
            for (int u = 0; u < n; u++) if (l[u] == -1 && dfs(u)) res++;
        }
        return res;
    }

    pair<vector<int>, vector<int>> min_vertex_cover() {
        vector<char> vis_l(n, false), vis_r(m, false);
        function<void(int)> go = [&](int u) {
            vis_l[u] = true;
            for (int v : adj[u]) {
                if (vis_r[v]) continue;
                vis_r[v] = true;
                if (r[v] != -1 && !vis_l[r[v]]) go(r[v]);
            }
            };
        for (int u = 0; u < n; u++) if (l[u] == -1 && !vis_l[u]) go(u);
        vector<int> left, right;
        for (int u = 0; u < n; u++) if (!vis_l[u]) left.push_back(u);
        for (int v = 0; v < m; v++) if (vis_r[v]) right.push_back(v);
        return {left, right};
    }
};

void solve() {
    ll l, r, m;
    cin >> l >> r >> m;
    HopcroftKarp hk(l, r);
    for (ll i = 0; i < m; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        hk.add_edge(ai, bi);
    }
    ll sz = hk.max_matching();
    cout << sz << "\n";
    for (ll i = 0; i < l; i++) {
        if (hk.l[i] != -1) cout << i << " " << hk.l[i] << "\n";
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
