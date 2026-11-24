// Contents
//   KShortestWalks  k shortest walks from s to t (Eppstein with a persistent leftist heap)
//   SimplePaths     k shortest simple paths from s to t (Yen's algorithm): no vertex repeats

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

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

// k shortest simple paths from s to t (Yen's algorithm): no vertex repeats, weights must be >= 0
// use KShortestWalks above when vertices may repeat, it is much faster; parallel edges count as different paths
//   SimplePaths(n)       empty directed graph on n vertices (add both directions for undirected), O(n)
//   add_edge(u, v, w)    add the directed edge u -> v, O(1)
//   dijkstra(a, t, ...)  shortest path from a to t avoiding the banned vertices and edges, O(E log V)
//   run(s, t, k)         up to k paths in increasing length as {length, vertices, edge ids}, O(k V E log V)
struct SimplePaths {
    struct Edge { int u, v; ll w; };
    struct Path {
        ll len;
        vector<int> verts, edges;
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> out;

    SimplePaths(int n = 0): n(n), out(n) {}

    void add_edge(int u, int v, ll w) {
        out[u].push_back(e.size());
        e.push_back({u, v, w});
    }

    // the edge ids of a shortest allowed path from a to t, and its length; length is INF if there is none
    pair<ll, vector<int>> dijkstra(int a, int t, const vector<char> &ban_v, const vector<char> &ban_e) const {
        vector<ll> dist(n, INF);
        vector<int> from(n, -1);
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        dist[a] = 0;
        pq.push({0, a});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            if (u == t) break;
            for (int id : out[u]) {
                int v = e[id].v;
                if (ban_e[id] || ban_v[v] || d + e[id].w >= dist[v]) continue;
                dist[v] = d + e[id].w;
                from[v] = id;
                pq.push({dist[v], v});
            }
        }
        if (dist[t] == INF) return {INF, {}};
        vector<int> path;
        for (int v = t; v != a; v = e[from[v]].u) path.push_back(from[v]);
        reverse(path.begin(), path.end());
        return {dist[t], path};
    }

    vector<Path> run(int s, int t, int k) const {
        vector<Path> res;
        if (k <= 0) return res;
        vector<char> ban_v(n, false), ban_e(e.size(), false);
        auto first = dijkstra(s, t, ban_v, ban_e);
        if (first.first == INF) return res;
        vector<vector<int>> found{first.second};  // edge ids of every path already returned
        set<pair<ll, vector<int>>> candidates;
        auto emit = [&](ll len, const vector<int> &edges) {
            vector<int> verts{s};
            for (int id : edges) verts.push_back(e[id].v);
            res.push_back({len, verts, edges});
        };
        emit(first.first, first.second);
        while ((int)res.size() < k) {
            const vector<int> prev = found.back();  // branch off the latest path at every position
            ll root_len = 0;
            int at = s;
            fill(ban_v.begin(), ban_v.end(), false);
            for (int i = 0; i < (int)prev.size(); i++) {
                vector<int> blocked;
                for (const vector<int> &p : found) {  // edges that would recreate a path already found
                    if ((int)p.size() > i && equal(p.begin(), p.begin() + i, prev.begin())) {
                        ban_e[p[i]] = true;
                        blocked.push_back(p[i]);
                    }
                }
                auto spur = dijkstra(at, t, ban_v, ban_e);
                for (int id : blocked) ban_e[id] = false;
                if (spur.first != INF) {
                    vector<int> full(prev.begin(), prev.begin() + i);
                    full.insert(full.end(), spur.second.begin(), spur.second.end());
                    candidates.insert({root_len + spur.first, full});
                }
                ban_v[at] = true;  // the root of the next branch can't be revisited
                root_len += e[prev[i]].w;
                at = e[prev[i]].v;
            }
            if (candidates.empty()) break;
            auto best = *candidates.begin();
            candidates.erase(candidates.begin());
            found.push_back(best.second);
            emit(best.first, best.second);
        }
        return res;
    }
};
