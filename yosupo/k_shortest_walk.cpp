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

// k shortest walks from s to t (Eppstein with a persistent leftist heap); walks may repeat vertices and edges, weights must be >= 0
//   KShortestWalks(n)    empty directed graph on n vertices, O(n)
//   add_edge(u, v, w)    add the directed edge u -> v, O(1)
//   merge(a, b)          persistent heap merge, O(log E)
//   run(s, t, k)         lengths of the k shortest walks in increasing order (fewer if there aren't k), O(E log E + V log V + k log k)
struct KShortestWalks {
    struct Edge { int u, v; ll w; };
    struct Node { ll key; int to, l, r, rank; };
    int n;
    vector<Edge> e;
    vector<Node> h;  // h[0] is the null heap

    KShortestWalks(int n = 0): n(n), h(1, Node{0, 0, 0, 0, 0}) {}

    void add_edge(int u, int v, ll w) { e.push_back({u, v, w}); }

    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (h[a].key > h[b].key) swap(a, b);
        h.push_back(h[a]);
        int id = h.size() - 1, r = merge(h[a].r, b);
        h[id].r = r;
        if (h[h[id].l].rank < h[r].rank) swap(h[id].l, h[id].r);
        h[id].rank = h[h[id].r].rank + 1;
        return id;
    }

    vector<ll> run(int s, int t, int k) {
        vector<vector<int>> in(n), out(n);
        for (int i = 0; i < (int)e.size(); i++) {
            in[e[i].v].push_back(i);
            out[e[i].u].push_back(i);
        }
        vector<ll> dist(n, INF);  // distance to t
        vector<int> tree(n, -1), order;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        dist[t] = 0;
        pq.push({0, t});
        while (!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();
            if (d != dist[v]) continue;
            order.push_back(v);
            for (int id : in[v]) {
                if (d + e[id].w < dist[e[id].u]) {
                    dist[e[id].u] = d + e[id].w;
                    tree[e[id].u] = id;
                    pq.push({dist[e[id].u], e[id].u});
                }
            }
        }
        if (dist[s] == INF || k <= 0) return {};
        vector<int> root(n, 0);  // root[v] = every detour available on the shortest path from v to t
        for (int v : order) {
            if (tree[v] != -1) root[v] = root[e[tree[v]].v];
            for (int id : out[v]) {
                if (id == tree[v] || dist[e[id].v] == INF) continue;
                h.push_back({e[id].w + dist[e[id].v] - dist[v], e[id].v, 0, 0, 1});
                int leaf = h.size() - 1, merged = merge(root[v], leaf);
                root[v] = merged;
            }
        }
        vector<ll> ans{dist[s]};
        priority_queue<pll, vector<pll>, greater<pll>> walks;  // {length, heap node}
        if (root[s]) walks.push({dist[s] + h[root[s]].key, root[s]});
        while (!walks.empty() && (int)ans.size() < k) {
            auto [d, x] = walks.top();
            walks.pop();
            ans.push_back(d);
            if (h[x].l) walks.push({d - h[x].key + h[h[x].l].key, h[x].l});
            if (h[x].r) walks.push({d - h[x].key + h[h[x].r].key, h[x].r});
            int next = root[h[x].to];
            if (next) walks.push({d + h[next].key, next});
        }
        return ans;
    }
};

void solve() {
    ll n, m, s, t, k;
    cin >> n >> m >> s >> t >> k;
    KShortestWalks ksw(n);
    for (ll i = 0; i < m; i++) {
        ll ui, vi, ci;
        cin >> ui >> vi >> ci;
        ksw.add_edge(ui, vi, ci);
    }
    vector<ll> ans = ksw.run(s, t, k);
    if (ans.size() < k) {
        ll need = k - ans.size();
        for (ll i = 0; i < need; i++) ans.push_back(-1);
    }
    for (ll i = 0; i < k; i++) cout << ans[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
