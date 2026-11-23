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

    bool dfs(int s) {  // iterative: call holds {left vertex, index of the edge being tried}
        vector<pair<int, int>> call{{s, 0}};
        while (!call.empty()) {
            auto [u, i] = call.back();
            if (i == (int)adj[u].size()) {  // dead end: never try u again this phase
                dist[u] = -1;
                call.pop_back();
                if (!call.empty()) call.back().second++;
                continue;
            }
            int v = adj[u][i];
            if (r[v] == -1) {  // free right vertex: flip the matching along the whole path
                for (auto [x, j] : call) {
                    l[x] = adj[x][j];
                    r[adj[x][j]] = x;
                }
                return true;
            }
            if (dist[r[v]] == dist[u] + 1) call.push_back({r[v], 0});
            else call.back().second++;
        }
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
        vector<int> st;  // alternating paths from the free left vertices
        for (int s = 0; s < n; s++) {
            if (l[s] != -1) continue;
            vis_l[s] = true;
            st.push_back(s);
        }
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : adj[u]) {
                if (vis_r[v]) continue;
                vis_r[v] = true;
                if (r[v] != -1 && !vis_l[r[v]]) {
                    vis_l[r[v]] = true;
                    st.push_back(r[v]);
                }
            }
        }
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
