// Contents
//   BinaryLift            binary lifting on a rooted tree, 0-indexed
//   LCA                   lowest common ancestor with O(1) queries (sparse table over DFS order), 0-indexed
//   HLD                   heavy-light decomposition, 0-indexed
//   CentroidDecomp        centroid decomposition, 0-indexed; example use: nearest painted vertex
//   TreeCanon             tree isomorphism by canonical ids (AHU); compare ids from the same TreeCanon object
//   tree_diameter         diameter of a weighted tree; returns {length, path}
//   dsu_on_tree           small-to-large on a tree (DSU on tree / sack)
//   virtual_tree          virtual tree of the vertices vs, using LCA above; returns {nodes, par}
//   cartesian_tree        parent of each index in the Cartesian tree of a (minimum at the root), -1 for the root
//   tree_distance_counts  cnt[d] = number of unordered pairs of vertices at distance d, O(n log^2 n);
//                         uses multiply (FFT)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// binary lifting on a rooted tree, 0-indexed
//   BinaryLift(adj, root)   preprocess the tree, O(n log n)
//   kth_ancestor(u, k)      k-th ancestor of u, -1 if it doesn't exist, O(log n)
//   is_ancestor(a, u)       true if a is an ancestor of u (or a == u), O(log n)
//   lca(u, v)               lowest common ancestor, O(log n)
struct BinaryLift {
    int n, lg;
    vector<int> dep;
    vector<vector<int>> up;

    BinaryLift(const vector<vector<int>> &adj, int root = 0): n(adj.size()), lg(1), dep(n, 0) {
        while ((1 << lg) < n) lg++;
        up.assign(lg, vector<int>(n, root));
        vector<int> st{root};
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : adj[u]) {
                if (v == up[0][u]) continue;
                up[0][v] = u;
                dep[v] = dep[u] + 1;
                st.push_back(v);
            }
        }
        for (int k = 1; k < lg; k++)
            for (int u = 0; u < n; u++) up[k][u] = up[k - 1][up[k - 1][u]];
    }

    int kth_ancestor(int u, int k) const {
        if (k > dep[u]) return -1;
        for (int i = 0; i < lg; i++) if (k >> i & 1) u = up[i][u];
        return u;
    }

    bool is_ancestor(int a, int u) const { return dep[a] <= dep[u] && kth_ancestor(u, dep[u] - dep[a]) == a; }

    int lca(int u, int v) const {
        if (dep[u] < dep[v]) swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if (u == v) return u;
        for (int k = lg - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];
    }
};

// lowest common ancestor with O(1) queries (sparse table over DFS order), 0-indexed
//   LCA(adj, root)   preprocess the tree, O(n log n)
//   lca(u, v)        lowest common ancestor, O(1)
struct LCA {
    int n;
    vector<int> tin, order;
    vector<vector<int>> st;  // st[0][i] = tin of the parent of the vertex with tin i

    LCA(const vector<vector<int>> &adj, int root = 0): n(adj.size()), tin(n), order(n) {
        st.assign(1, vector<int>(n, 0));
        vector<pair<int, int>> stk{{root, root}};
        int t = 0;
        while (!stk.empty()) {
            auto [u, p] = stk.back();
            stk.pop_back();
            order[t] = u;
            st[0][t] = tin[p];
            tin[u] = t++;
            for (int v : adj[u]) if (v != p) stk.push_back({v, u});
        }
        for (int j = 1; (1 << j) <= n; j++) {
            st.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }

    int lca(int u, int v) const {
        if (u == v) return u;
        int l = tin[u], r = tin[v];
        if (l > r) swap(l, r);
        l++;
        r++;
        int k = __lg(r - l);
        return order[min(st[k][l], st[k][r - (1 << k)])];
    }
};

// heavy-light decomposition, 0-indexed; maps paths and subtrees to ranges of pos[] for a segment tree on [l, r)
//   HLD(adj, root)              preprocess the tree, O(n)
//   lca(u, v)                   lowest common ancestor, O(log n)
//   path(u, v, f, skip_lca)     call f(l, r) or f(l, r, up) for each range on the path u - v, in order from u to v;
//                               up means the path walks the range from r - 1 down to l (for non-commutative ops);
//                               skip_lca leaves out the lca (for edge values), O(log n) calls
//   subtree(u)                  range {l, r} of the subtree of u, O(1)
struct HLD {
    int n;
    vector<int> par, dep, sz, heavy, head, pos;

    HLD(const vector<vector<int>> &adj, int root = 0)
        : n(adj.size()), par(n, -1), dep(n, 0), sz(n, 1), heavy(n, -1), head(n, root), pos(n, 0) {
        vector<int> order{root};
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == par[u]) continue;
                par[v] = u;
                dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i], p = par[u];
            sz[p] += sz[u];
            if (heavy[p] == -1 || sz[u] > sz[heavy[p]]) heavy[p] = u;
        }
        for (int u : order) {  // the heavy child comes first, so each chain and each subtree is contiguous
            int next = pos[u] + 1;
            if (heavy[u] != -1) {
                head[heavy[u]] = head[u];
                pos[heavy[u]] = next;
                next += sz[heavy[u]];
            }
            for (int v : adj[u]) {
                if (v == par[u] || v == heavy[u]) continue;
                head[v] = v;
                pos[v] = next;
                next += sz[v];
            }
        }
    }

    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            v = par[head[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    template <class F>
    void path(int u, int v, F f, bool skip_lca = false) const {
        auto call = [&](int l, int r, bool up) {
            if constexpr (is_invocable_v<F, int, int, bool>) f(l, r, up);
            else f(l, r);
        };
        vector<pair<int, int>> down;  // ranges on the v side, called last in reverse
        while (head[u] != head[v]) {
            if (dep[head[u]] >= dep[head[v]]) {
                call(pos[head[u]], pos[u] + 1, true);
                u = par[head[u]];
            } else {
                down.push_back({pos[head[v]], pos[v] + 1});
                v = par[head[v]];
            }
        }
        if (dep[u] >= dep[v]) {
            if (pos[v] + skip_lca < pos[u] + 1) call(pos[v] + skip_lca, pos[u] + 1, true);
        } else if (pos[u] + skip_lca < pos[v] + 1) {
            call(pos[u] + skip_lca, pos[v] + 1, false);
        }
        for (int i = (int)down.size() - 1; i >= 0; i--) call(down[i].first, down[i].second, false);
    }

    pair<int, int> subtree(int u) const { return {pos[u], pos[u] + sz[u]}; }
};

// centroid decomposition, 0-indexed; example use: nearest painted vertex
//   CentroidDecomp(adj)   build the decomposition, O(n log n)
//   bfs(s)                unremoved component of s in BFS order, filling par[] and dist[] from s, O(component size)
//   build(u)              decompose the component of u (recursion depth O(log n)), O(n log n) total
//   paint(u)              mark u as painted, O(log n)
//   closest(u)            distance to the nearest painted vertex, NO_PAINT if there is none, O(log n)
struct CentroidDecomp {
    static constexpr int NO_PAINT = 1e9;
    int n;
    vector<vector<int>> adj;
    vector<char> removed;
    vector<int> sz, best, par, dist;
    vector<vector<pair<int, int>>> anc;  // anc[u] = {centroid ancestor, distance to it}

    CentroidDecomp(const vector<vector<int>> &adj)
        : n(adj.size()), adj(adj), removed(n), sz(n), best(n, NO_PAINT), par(n), dist(n), anc(n) {
        if (n) build(0);
    }

    vector<int> bfs(int s) {
        vector<int> order{s};
        par[s] = -1;
        dist[s] = 0;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == par[u] || removed[v]) continue;
                par[v] = u;
                dist[v] = dist[u] + 1;
                order.push_back(v);
            }
        }
        return order;
    }

    void build(int s) {
        vector<int> order = bfs(s);
        for (int i = (int)order.size() - 1; i >= 0; i--) {  // subtree sizes, children before parents
            int u = order[i];
            sz[u] = 1;
            for (int v : adj[u]) if (v != par[u] && !removed[v]) sz[u] += sz[v];
        }
        int total = order.size(), c = s;
        for (bool moved = true; moved;) {  // walk toward the heavy child until none has more than half
            moved = false;
            for (int v : adj[c]) {
                if (v != par[c] && !removed[v] && sz[v] * 2 > total) {
                    c = v;
                    moved = true;
                    break;
                }
            }
        }
        for (int u : bfs(c)) anc[u].push_back({c, dist[u]});
        removed[c] = true;
        for (int v : adj[c]) if (!removed[v]) build(v);
    }

    void paint(int u) {
        for (auto [c, d] : anc[u]) best[c] = min(best[c], d);
    }

    int closest(int u) const {
        int res = NO_PAINT;
        for (auto [c, d] : anc[u]) if (best[c] != NO_PAINT) res = min(res, d + best[c]);
        return res;
    }
};

// tree isomorphism by canonical ids (AHU); compare ids from the same TreeCanon object
//   rooted(adj, root)   ids of the subtree of every vertex when rooted at root (the tree's id is [root]):
//                       equal ids means isomorphic, and ids are 0..ids.size()-1 in order of first appearance,
//                       O(n log n)
//   centers(adj)        the 1 or 2 centers of the tree, O(n)
//   unrooted(adj)       id of the unrooted tree: equal ids means isomorphic, O(n log n)
struct TreeCanon {
    map<vector<int>, int> ids;

    vector<int> rooted(const vector<vector<int>> &adj, int root) {
        int n = adj.size();
        vector<int> order{root}, par(n, -1), id(n);
        for (int i = 0; i < (int)order.size(); i++) {
            for (int v : adj[order[i]]) {
                if (v == par[order[i]]) continue;
                par[v] = order[i];
                order.push_back(v);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            vector<int> kids;
            for (int v : adj[u]) if (v != par[u]) kids.push_back(id[v]);
            sort(kids.begin(), kids.end());
            id[u] = ids.try_emplace(kids, ids.size()).first->second;
        }
        return id;
    }

    vector<int> centers(const vector<vector<int>> &adj) {
        int n = adj.size(), left = n;
        if (n <= 2) {
            vector<int> c(n);
            iota(c.begin(), c.end(), 0);
            return c;
        }
        vector<int> deg(n), layer;
        for (int u = 0; u < n; u++) {
            deg[u] = adj[u].size();
            if (deg[u] == 1) layer.push_back(u);
        }
        while (left > 2) {
            left -= layer.size();
            vector<int> next;
            for (int u : layer) for (int v : adj[u]) if (--deg[v] == 1) next.push_back(v);
            layer = next;
        }
        return layer;
    }

    int unrooted(const vector<vector<int>> &adj) {
        int res = INT_MAX;
        for (int c : centers(adj)) res = min(res, rooted(adj, c)[c]);
        return res;
    }
};

// diameter of a tree with edge weights >= 0, 0-indexed; adj[u] = {v, w}, use w = 1 for unweighted
// returns {length, path}, path = the vertices from one end of the diameter to the other, O(n)
pair<ll, vector<int>> tree_diameter(const vector<vector<pair<int, ll>>> &adj) {
    int n = adj.size();
    vector<int> par(n);
    vector<ll> dist(n);
    auto farthest = [&](int s) {  // fills par and dist from s, returns the vertex farthest from s
        fill(par.begin(), par.end(), -1);
        dist[s] = 0;
        vector<int> stk{s};
        int best = s;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            if (dist[u] > dist[best]) best = u;
            for (auto [v, w] : adj[u]) {
                if (v == par[u]) continue;
                par[v] = u, dist[v] = dist[u] + w;
                stk.push_back(v);
            }
        }
        return best;
    };
    int b = farthest(farthest(0));
    vector<int> path;
    for (int v = b; v != -1; v = par[v]) path.push_back(v);
    return {dist[b], path};
}

// small-to-large on a tree (DSU on tree / sack): subtree queries in O(n log n) add/remove calls
// answer(v) is called when exactly the vertices of v's subtree have been added
template <class Add, class Remove, class Answer>
void dsu_on_tree(const vector<vector<int>> &adj, int root, Add add, Remove remove, Answer answer) {
    int n = adj.size();
    vector<int> par(n, -1), tin(n), sz(n, 1), heavy(n, -1), order;
    vector<int> st{root};
    while (!st.empty()) {  // any preorder keeps each subtree contiguous
        int u = st.back();
        st.pop_back();
        tin[u] = order.size();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            st.push_back(v);
        }
    }
    for (int i = n - 1; i > 0; i--) {
        int u = order[i], p = par[u];
        sz[p] += sz[u];
        if (heavy[p] == -1 || sz[u] > sz[heavy[p]]) heavy[p] = u;
    }
    struct Frame { int v; bool keep, done; };
    vector<Frame> stk{{root, false, false}};
    while (!stk.empty()) {
        auto [v, keep, done] = stk.back();
        stk.pop_back();
        if (!done) {  // visit the light children first and clear them, then keep the heavy child
            stk.push_back({v, keep, true});
            if (heavy[v] != -1) stk.push_back({heavy[v], true, false});
            for (int u : adj[v]) if (u != par[v] && u != heavy[v]) stk.push_back({u, false, false});
            continue;
        }
        add(v);
        for (int u : adj[v]) {
            if (u == par[v] || u == heavy[v]) continue;
            for (int i = tin[u]; i < tin[u] + sz[u]; i++) add(order[i]);
        }
        answer(v);
        if (!keep) {
            for (int i = tin[v]; i < tin[v] + sz[v]; i++) remove(order[i]);
        }
    }
}

// virtual tree of the vertices vs, using LCA above; returns {nodes, par}, nodes sorted by DFS order and containing vs
// and all their pairwise LCAs, par[i] = the parent vertex of nodes[i] in the virtual tree (-1 for the first),
// O(k log k)
pair<vector<int>, vector<int>> virtual_tree(vector<int> vs, const LCA &l) {
    auto by_tin = [&](int a, int b) { return l.tin[a] < l.tin[b]; };
    sort(vs.begin(), vs.end(), by_tin);
    int k = vs.size();
    for (int i = 0; i + 1 < k; i++) vs.push_back(l.lca(vs[i], vs[i + 1]));
    sort(vs.begin(), vs.end(), by_tin);
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    vector<int> par(vs.size(), -1);
    for (int i = 1; i < (int)vs.size(); i++) par[i] = l.lca(vs[i - 1], vs[i]);
    return {vs, par};
}

// parent of each index in the Cartesian tree of a: the minimum is the root, and each side of it recursively
// (equal values: the leftmost is the ancestor); -1 for the root, O(n)
vector<int> cartesian_tree(const vector<ll> &a) {
    int n = a.size();
    vector<int> par(n, -1), st;
    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!st.empty() && a[st.back()] > a[i]) {
            last = st.back();
            st.pop_back();
        }
        if (last != -1) par[last] = i;
        if (!st.empty()) par[i] = st.back();
        st.push_back(i);
    }
    return par;
}

// cnt[d] = number of unordered pairs u != v at distance d in a tree, d = 0..n-1 (cnt[0] = 0); uses multiply (FFT)
// centroid decomposition: square the depth counts around each centroid, minus the square inside each child subtree
// (pairs whose path does not pass through the centroid), O(n log^2 n)
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b);  // exact integer product, from fft.cpp
vector<ll> tree_distance_counts(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<ll> cnt(n);
    vector<char> removed(n);
    vector<int> par(n), dep(n), sz(n), todo{0};
    auto bfs = [&](int s, int p, int d) {  // unremoved component of s in BFS order, filling par[] and dep[]
        vector<int> order{s};
        par[s] = p, dep[s] = d;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == par[u] || removed[v]) continue;
                par[v] = u, dep[v] = dep[u] + 1;
                order.push_back(v);
            }
        }
        return order;
    };
    auto count = [&](const vector<int> &order, int sign) {  // add sign * (ordered pairs by depth sum)
        vector<ll> a(dep[order.back()] + 1);
        for (int u : order) a[dep[u]]++;
        vector<ll> sq = multiply(a, a);
        if (sq.size() > cnt.size()) cnt.resize(sq.size());
        for (int d = 0; d < (int)sq.size(); d++) cnt[d] += sign * sq[d];
    };
    while (n && !todo.empty()) {
        int s = todo.back();
        todo.pop_back();
        vector<int> order = bfs(s, -1, 0);
        for (int i = (int)order.size() - 1; i >= 0; i--) {  // subtree sizes, children before parents
            int u = order[i];
            sz[u] = 1;
            for (int v : adj[u]) if (v != par[u] && !removed[v]) sz[u] += sz[v];
        }
        int total = order.size(), c = s;
        for (bool moved = true; moved;) {  // walk toward the heavy child until none has more than half
            moved = false;
            for (int v : adj[c]) {
                if (v != par[c] && !removed[v] && sz[v] * 2 > total) {
                    c = v;
                    moved = true;
                    break;
                }
            }
        }
        count(bfs(c, -1, 0), 1);
        removed[c] = true;
        for (int v : adj[c]) {
            if (removed[v]) continue;
            count(bfs(v, c, 1), -1);
            todo.push_back(v);
        }
    }
    cnt.resize(n);
    for (ll &x : cnt) x /= 2;
    if (n) cnt[0] = 0;
    return cnt;
}
