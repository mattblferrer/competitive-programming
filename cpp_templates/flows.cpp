#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// Dinic's algorithm, O(V^2 E)
// after max_flow: e[id].f is the flow on edge id (returned by connect_*),
// and level[v] != -1 means v is on the source side of a min cut
//   Flow(n)                  empty network on n vertices (0-indexed), O(n)
//   resize_flow(n)           reset to an empty network on n vertices, O(n)
//   connect_d(u, v, w, rw)   add directed edge u -> v with capacity w (reverse capacity rw), returns edge id, O(1)
//   connect_u(u, v, w)       add undirected edge u - v with capacity w, returns edge id, O(1)
//   bfs(s, t)                build the level graph from s; true if t is reachable, O(V + E)
//   dfs(u, t, pushed)        find one augmenting path in the level graph and push flow along it, returns amount pushed
//   max_flow(s, t)           max flow from s to t, O(V^2 E) (O(E sqrt V) on unit-capacity graphs)
struct Flow {
    struct Edge { int to; ll cap, f; };
    vector<Edge> e;  // e[id ^ 1] is the reverse edge of e[id]
    vector<vector<int>> adj;  // edge ids leaving each vertex
    vector<int> level, ptr;

    Flow(int n = 0) { resize_flow(n); }

    void resize_flow(int n) {
        e.clear();
        adj.assign(n, {});
        level.resize(n);
        ptr.resize(n);
    }

    int connect_d(int u, int v, ll w, ll rw = 0) {
        adj[u].push_back(e.size()); e.push_back({v, w, 0});
        adj[v].push_back(e.size()); e.push_back({u, rw, 0});
        return e.size() - 2;
    }

    int connect_u(int u, int v, ll w) { return connect_d(u, v, w, w); }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                if (e[id].cap > e[id].f && level[e[id].to] == -1) {
                    level[e[id].to] = level[u] + 1;
                    q.push(e[id].to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, int t, ll pushed) {
        if (u == t || !pushed) return pushed;
        for (int &i = ptr[u]; i < (int)adj[u].size(); i++) {
            Edge &ed = e[adj[u][i]];
            if (level[ed.to] != level[u] + 1 || ed.cap == ed.f) continue;
            ll got = dfs(ed.to, t, min(pushed, ed.cap - ed.f));
            if (got) {
                ed.f += got;
                e[adj[u][i] ^ 1].f -= got;
                return got;
            }
        }
        return 0;
    }

    ll max_flow(int s, int t) {
        ll f = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, INF)) f += pushed;
        }
        return f;
    }
};

// all-pairs max flow on an undirected graph (Gomory-Hu tree), uses Flow above
// build g with connect_u; the flows stored in g are reset
//   GomoryHu(g)      build the tree with n - 1 max flows, O(V^3 E)
//   query(s, t)      max flow between s and t, O(V)
struct GomoryHu {
    int n;
    vector<int> dep, par;
    vector<ll> w;  // w[v] = capacity of the tree edge from v to par[v]

    GomoryHu(Flow &g): n(g.adj.size()), dep(n, 0), par(n, 0), w(n, 0) {
        for (int u = 1; u < n; u++) {
            for (auto &ed : g.e) ed.f = 0;
            w[u] = g.max_flow(u, par[u]);
            for (int v = u + 1; v < n; v++)
                if (g.level[v] != -1 && par[v] == par[u]) par[v] = u;
            dep[u] = dep[par[u]] + 1;
        }
    }

    ll query(int s, int t) const {
        ll ans = INF;
        while (s != t) {
            if (dep[s] < dep[t]) swap(s, t);
            ans = min(ans, w[s]);
            s = par[s];
        }
        return ans;
    }
};
