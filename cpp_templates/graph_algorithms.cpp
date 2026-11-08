#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// strongly connected components (Tarjan), 0-indexed
// component ids are in reverse topological order: an edge u -> v between components has comp[u] > comp[v]
//   SCC(n)         empty graph on n vertices, O(n)
//   add_edge(u, v) add the directed edge u -> v, O(1)
//   dfs(u)         visit u and pop finished components, O(V + E) total
//   run()          compute comp[] and returns the number of components, O(V + E)
struct SCC {
    int n, timer = 0, count = 0;
    vector<vector<int>> adj;
    vector<int> id, low, comp, st;

    SCC(int n = 0): n(n), adj(n), id(n, -1), low(n), comp(n, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    void dfs(int u) {
        id[u] = low[u] = timer++;
        st.push_back(u);
        for (int v : adj[u]) {
            if (id[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (comp[v] == -1) {
                low[u] = min(low[u], id[v]);
            }
        }
        if (id[u] == low[u]) {
            int v;
            do {
                v = st.back();
                st.pop_back();
                comp[v] = count;
            } while (v != u);
            count++;
        }
    }

    int run() {
        for (int u = 0; u < n; u++) if (id[u] == -1) dfs(u);
        return count;
    }
};

// 2-SAT, uses SCC above
//   TwoSat(n)              n boolean variables, O(n)
//   add_or(a, fa, b, fb)   require (a == fa) or (b == fb), O(1)
//   solve()                true if satisfiable, and fills val[i] with a valid assignment, O(n + clauses)
struct TwoSat {
    int n;
    SCC scc;
    vector<char> val;

    TwoSat(int n = 0): n(n), scc(2 * n), val(n) {}

    void add_or(int a, bool fa, int b, bool fb) {
        scc.add_edge(2 * a + !fa, 2 * b + fb);
        scc.add_edge(2 * b + !fb, 2 * a + fa);
    }

    bool solve() {
        scc.run();
        for (int i = 0; i < n; i++) {
            if (scc.comp[2 * i] == scc.comp[2 * i + 1]) return false;
            val[i] = scc.comp[2 * i + 1] < scc.comp[2 * i];  // node 2i + 1 is "i is true"
        }
        return true;
    }
};

// smallest average edge weight over all directed cycles (Karp), INF if the graph is acyclic, O(VE)
// edges are {u, v, w}
ld min_mean_cycle(int n, const vector<array<ll, 3>> &edges) {
    vector<vector<ll>> dp(n + 1, vector<ll>(n, INF));
    fill(dp[0].begin(), dp[0].end(), 0);
    for (int k = 1; k <= n; k++) {
        for (auto &[u, v, w] : edges) {
            if (dp[k - 1][u] < INF) dp[k][v] = min(dp[k][v], dp[k - 1][u] + w);
        }
    }
    ld best = INF;
    for (int u = 0; u < n; u++) {
        if (dp[n][u] == INF) continue;
        ld worst = -INF;
        for (int k = 0; k < n; k++) {
            if (dp[k][u] < INF) worst = max(worst, (ld)(dp[n][u] - dp[k][u]) / (n - k));
        }
        best = min(best, worst);
    }
    return best;
}

// bridges, articulation points and biconnected components of an undirected graph; multi-edges are handled correctly
//   Biconnected(n)        empty graph on n vertices, O(n)
//   add_edge(u, v)        add the undirected edge u - v, returns its id, O(1)
//   dfs(u, pe)            visit u, entered through edge pe, O(V + E) total
//   run()                 fills is_bridge[id], artics, and blocks (vertex lists), O(V + E)
//   block_cut_tree(node)  tree whose nodes are the artics then the blocks; node[u] is u's tree node (-1 if isolated), O(V + E)
//   bridge_tree(comp)     tree of 2-edge-connected components; comp[u] is u's tree node, O(V + E)
struct Biconnected {
    int n, m = 0, timer = 0;
    vector<vector<pair<int, int>>> adj;  // {to, edge id}
    vector<int> disc, low, stk, artics;
    vector<vector<int>> blocks;
    vector<char> is_bridge;
    vector<pair<int, int>> edges;

    Biconnected(int n = 0): n(n), adj(n) {}

    int add_edge(int u, int v) {
        adj[u].push_back({v, m});
        adj[v].push_back({u, m});
        edges.push_back({u, v});
        return m++;
    }

    void dfs(int u, int pe) {
        disc[u] = low[u] = timer++;
        stk.push_back(u);
        int children = 0;
        bool cut = false;
        for (auto [v, id] : adj[u]) {
            if (id == pe) continue;
            if (disc[v] == -1) {
                dfs(v, id);
                children++;
                low[u] = min(low[u], low[v]);
                if (disc[u] < low[v]) is_bridge[id] = true;
                if (disc[u] <= low[v]) {
                    cut = true;
                    blocks.push_back({u});
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        blocks.back().push_back(x);
                    } while (x != v);
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (pe == -1 ? children >= 2 : cut) artics.push_back(u);
    }

    void run() {
        disc.assign(n, -1);
        low.assign(n, 0);
        is_bridge.assign(m, false);
        for (int u = 0; u < n; u++) {
            if (disc[u] == -1) {
                dfs(u, -1);
                stk.clear();
            }
        }
    }

    vector<vector<int>> block_cut_tree(vector<int> &node) {
        int a = artics.size();
        vector<vector<int>> tree(a + blocks.size());
        node.assign(n, -1);
        vector<char> is_art(n, false);
        for (int i = 0; i < a; i++) {
            node[artics[i]] = i;
            is_art[artics[i]] = true;
        }
        for (int i = 0; i < (int)blocks.size(); i++) {
            for (int u : blocks[i]) {
                if (is_art[u]) {
                    tree[node[u]].push_back(a + i);
                    tree[a + i].push_back(node[u]);
                } else {
                    node[u] = a + i;
                }
            }
        }
        return tree;
    }

    vector<vector<int>> bridge_tree(vector<int> &comp) {
        comp.assign(n, -1);
        int c = 0;
        for (int s = 0; s < n; s++) {
            if (comp[s] != -1) continue;
            vector<int> st{s};
            comp[s] = c;
            while (!st.empty()) {
                int u = st.back();
                st.pop_back();
                for (auto [v, id] : adj[u]) {
                    if (!is_bridge[id] && comp[v] == -1) {
                        comp[v] = c;
                        st.push_back(v);
                    }
                }
            }
            c++;
        }
        vector<vector<int>> tree(c);
        for (int id = 0; id < m; id++) {
            if (!is_bridge[id]) continue;
            int a = comp[edges[id].first], b = comp[edges[id].second];
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        return tree;
    }
};

// minimum spanning forest (Kruskal), edges are {w, u, v}; returns {total weight, indices of the chosen edges}, O(E log E)
pair<ll, vector<int>> kruskal(int n, const vector<array<ll, 3>> &edges) {
    vector<int> p(n), order(edges.size()), chosen;
    iota(p.begin(), p.end(), 0);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return edges[a] < edges[b]; });
    function<int(int)> find_set = [&](int x) { return p[x] == x ? x : p[x] = find_set(p[x]); };
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

// Euler path/cycle in a directed graph, as a vertex list of length E + 1; empty if none exists, O(V + E)
vector<int> euler_directed(int n, const vector<pair<int, int>> &edges) {
    vector<vector<int>> adj(n);
    vector<int> in(n), out(n);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        out[u]++;
        in[v]++;
    }
    int start = -1, end = -1, any = -1;
    for (int u = 0; u < n; u++) {
        if (out[u] > 0 && any == -1) any = u;
        if (out[u] == in[u] + 1) {
            if (start != -1) return {};
            start = u;
        } else if (in[u] == out[u] + 1) {
            if (end != -1) return {};
            end = u;
        } else if (in[u] != out[u]) {
            return {};
        }
    }
    if (n == 0 || (start == -1) != (end == -1)) return {};
    if (start == -1) start = any == -1 ? 0 : any;
    vector<int> st{start}, path;
    while (!st.empty()) {
        int u = st.back();
        if (adj[u].empty()) {
            path.push_back(u);
            st.pop_back();
        } else {
            st.push_back(adj[u].back());
            adj[u].pop_back();
        }
    }
    reverse(path.begin(), path.end());
    if (path.size() != edges.size() + 1) return {};
    return path;
}

// Euler path/cycle in an undirected graph, as a vertex list of length E + 1; empty if none exists, O(V + E)
vector<int> euler_undirected(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> adj(n);
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }
    int start = -1, odd = 0;
    for (int u = 0; u < n; u++) {
        if (deg[u] > 0 && start == -1) start = u;
        if (deg[u] % 2) odd++;
    }
    for (int u = 0; u < n; u++) if (deg[u] % 2) start = u;  // a path must start at an odd-degree vertex
    if (n == 0 || (odd != 0 && odd != 2)) return {};
    if (start == -1) start = 0;
    vector<char> used(m, false);
    vector<int> st{start}, path;
    while (!st.empty()) {
        int u = st.back();
        while (!adj[u].empty() && used[adj[u].back().second]) adj[u].pop_back();
        if (adj[u].empty()) {
            path.push_back(u);
            st.pop_back();
        } else {
            auto [v, id] = adj[u].back();
            used[id] = true;
            st.push_back(v);
        }
    }
    if ((int)path.size() != m + 1) return {};
    return path;
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

// cliques in a graph on at most N vertices, exponential in the worst case; a maximum independent set is a maximum clique of the complement
//   MaxClique(n)       empty graph on n vertices, O(n)
//   add_edge(u, v)     add the undirected edge u - v (self-loops are ignored), O(1)
//   enumerate(f)       call f(r) with a bitset r for every maximal clique (Bron-Kerbosch with pivoting), O(3^(n/3)) calls at most
//   max_clique()       vertices of a maximum clique (branch and bound with a greedy coloring bound)
template <int N = 128>
struct MaxClique {
    using B = bitset<N>;
    int n;
    vector<B> adj;
    vector<int> cur, best;

    MaxClique(int n = 0): n(n), adj(n) {}

    void add_edge(int u, int v) {
        if (u == v) return;
        adj[u].set(v);
        adj[v].set(u);
    }

    template <class F>
    void go(B r, B p, B x, F &f) {
        if (p.none()) {
            if (x.none()) f(r);
            return;
        }
        B both = p | x;
        int pivot = -1, most = -1;
        for (int v = both._Find_first(); v < N; v = both._Find_next(v)) {
            int c = (p & adj[v]).count();
            if (c > most) most = c, pivot = v;
        }
        B cand = p & ~adj[pivot];
        for (int v = cand._Find_first(); v < N; v = cand._Find_next(v)) {
            B with = r;
            with.set(v);
            go(with, p & adj[v], x & adj[v], f);
            p.reset(v);
            x.set(v);
        }
    }

    template <class F>
    void enumerate(F f) {
        B p;
        for (int i = 0; i < n; i++) p.set(i);
        go(B(), p, B(), f);
    }

    void expand(B p) {
        vector<int> order, color;
        B left = p;
        for (int c = 1; left.any(); c++) {  // vertices of one color are pairwise non-adjacent, so a clique uses at most one of them
            B q = left;
            while (q.any()) {
                int v = q._Find_first();
                order.push_back(v);
                color.push_back(c);
                left.reset(v);
                q.reset(v);
                q &= ~adj[v];
            }
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            if (cur.size() + color[i] <= best.size()) return;
            int v = order[i];
            cur.push_back(v);
            B np = p & adj[v];
            if (np.any()) expand(np);
            else if (cur.size() > best.size()) best = cur;
            cur.pop_back();
            p.reset(v);
        }
    }

    vector<int> max_clique() {
        B p;
        for (int i = 0; i < n; i++) p.set(i);
        cur.clear();
        best.clear();
        expand(p);
        sort(best.begin(), best.end());
        return best;
    }
};

// fewest colors for a proper vertex coloring (inclusion-exclusion over independent sets), O(2^n n) time, O(2^n) memory, n up to about 23
// checks two primes, so a wrong answer needs both to cancel by chance; edges are {u, v}, self-loops are ignored
int chromatic_number(int n, const vector<pair<int, int>> &edges) {
    if (n == 0) return 0;
    const ll M1 = 998'244'353, M2 = 1'000'000'007;
    vector<int> adj(n);
    for (auto [u, v] : edges) {
        if (u == v) continue;
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }
    int full = 1 << n;
    vector<int> ind(full, 1), g1(full, 1), g2(full, 1);  // ind[S] = number of independent subsets of S
    for (int s = 1; s < full; s++) {
        int v = __builtin_ctz(s), rest = s ^ (1 << v);
        ind[s] = ind[rest] + ind[rest & ~adj[v]];
    }
    for (int k = 1; k < n; k++) {  // g[S] = ways to choose k independent sets inside S, in order
        ll s1 = 0, s2 = 0;
        for (int s = 0; s < full; s++) {
            g1[s] = g1[s] * (ll)ind[s] % M1;
            g2[s] = g2[s] * (ll)ind[s] % M2;
            bool neg = (n - __builtin_popcount(s)) & 1;
            s1 += neg ? M1 - g1[s] : g1[s];
            s2 += neg ? M2 - g2[s] : g2[s];
        }
        if (s1 % M1 != 0 || s2 % M2 != 0) return k;
    }
    return n;
}

// weight of the cheapest connected subgraph containing all terminals (Steiner tree), INF if impossible; k = number of terminals
// adj[u] holds {v, w} for both directions of each edge, w >= 0, O(3^k V + 2^k E log V)
ll steiner_tree(const vector<vector<pair<int, ll>>> &adj, const vector<int> &terminals) {
    int n = adj.size(), k = terminals.size();
    if (k == 0) return 0;
    vector<vector<ll>> dp(1 << k, vector<ll>(n, INF));  // dp[mask][v] = cheapest tree containing mask and v
    for (int i = 0; i < k; i++) dp[1 << i][terminals[i]] = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        vector<ll> &d = dp[mask];
        for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
            if (sub < (mask ^ sub)) continue;  // each split only needs trying once
            for (int v = 0; v < n; v++) {
                if (dp[sub][v] < INF && dp[mask ^ sub][v] < INF) d[v] = min(d[v], dp[sub][v] + dp[mask ^ sub][v]);
            }
        }
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        for (int v = 0; v < n; v++) if (d[v] < INF) pq.push({d[v], v});
        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();
            if (cost != d[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (cost + w < d[v]) {
                    d[v] = cost + w;
                    pq.push({d[v], v});
                }
            }
        }
    }
    return dp[(1 << k) - 1][terminals[0]];
}

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
