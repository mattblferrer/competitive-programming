// Contents
//   kruskal         minimum spanning forest (Kruskal), edges are {w, u, v}
//   Arborescence    minimum spanning arborescence (Chu-Liu/Edmonds)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// minimum spanning forest (Kruskal), edges are {w, u, v}; returns {total weight, indices of the chosen edges}, O(E log E)
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

// minimum spanning arborescence (Chu-Liu/Edmonds): every vertex is reachable from root by chosen edges
// call find_min only once per object, since it contracts the graph
//   Arborescence(n)     empty graph on n vertices, O(n)
//   add_edge(u, v, w)   add the directed edge u -> v, returns its id, O(1)
//   find_min(root)      for each vertex, the id of the edge entering it (-1 for root); empty if impossible, O(VE)
struct Arborescence {
    struct Edge { int from, to; ll w; };
    struct UnionFind {
        vector<int> p;
        UnionFind(int n = 0): p(n, -1) {}
        int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
        void unite(int x, int y) {
            x = find(x), y = find(y);
            if (x == y) return;
            if (p[x] > p[y]) swap(x, y);
            p[x] += p[y];
            p[y] = x;
        }
    };
    int n;
    vector<Edge> e;
    UnionFind uf;
    vector<vector<pair<int, ll>>> adj;  // adj[v] = edges entering v, as {edge id, current weight}

    Arborescence(int n = 0): n(n), uf(n), adj(n) {}

    int add_edge(int u, int v, ll w) {
        e.push_back({u, v, w});
        adj[v].push_back({(int)e.size() - 1, w});
        return e.size() - 1;
    }

    vector<int> find_min(int r) {
        vector<int> vis(n, -1), par(n, -1);
        vector<ll> mn(n, INF);
        for (int i = 0; i < n; i++) {
            if (uf.find(i) != i) continue;
            int at = i;
            while (at != r && vis[at] == -1) {
                vis[at] = i;
                for (auto [id, w] : adj[at]) {
                    if (w < mn[at] && uf.find(e[id].from) != at) {
                        mn[at] = w;
                        par[at] = id;
                    }
                }
                if (par[at] == -1) return {};
                at = uf.find(e[par[at]].from);
            }
            if (at == r || vis[at] != i) continue;
            UnionFind before = uf;  // found a cycle: contract it and solve the smaller graph
            vector<int> seq;
            do {
                seq.push_back(at);
                at = uf.find(e[par[at]].from);
            } while (at != seq.front());
            for (int v : seq) uf.unite(v, seq[0]);
            int c = uf.find(seq[0]);
            vector<pair<int, ll>> merged;
            for (int v : seq) for (auto [id, w] : adj[v]) merged.push_back({id, w - mn[v]});
            adj[c] = merged;
            vector<int> rest = find_min(r);
            if (rest.empty()) return rest;
            int use = rest[c];
            rest[at = before.find(e[use].to)] = use;
            for (int v : seq) if (v != at) rest[v] = par[v];
            return rest;
        }
        return par;
    }
};
