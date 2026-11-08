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
//   path(u, v, f, skip_lca)     call f(l, r) for each range on the path u - v; skip_lca leaves out the lca (for edge values), O(log n) calls
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
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            f(pos[head[v]], pos[v] + 1);
            v = par[head[v]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        if (pos[u] + skip_lca < pos[v] + 1) f(pos[u] + skip_lca, pos[v] + 1);
    }

    pair<int, int> subtree(int u) const { return {pos[u], pos[u] + sz[u]}; }
};

// centroid decomposition, 0-indexed; example use: nearest painted vertex
//   CentroidDecomp(adj)   build the decomposition, O(n log n)
//   calc_size(u, p)       subtree sizes among unremoved vertices, O(component size)
//   find_centroid(u, p, total)   centroid of the component of u, O(component size)
//   add_dist(u, p, c, d)  record centroid c at distance d for every vertex below u, O(component size)
//   build(u)              decompose the component of u, O(n log n) total
//   paint(u)              mark u as painted, O(log n)
//   closest(u)            distance to the nearest painted vertex, NO_PAINT if there is none, O(log n)
struct CentroidDecomp {
    static constexpr int NO_PAINT = 1e9;
    int n;
    vector<vector<int>> adj;
    vector<char> removed;
    vector<int> sz, best;
    vector<vector<pair<int, int>>> anc;  // anc[u] = {centroid ancestor, distance to it}

    CentroidDecomp(const vector<vector<int>> &adj): n(adj.size()), adj(adj), removed(n), sz(n), best(n, NO_PAINT), anc(n) {
        if (n) build(0);
    }

    int calc_size(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) if (v != p && !removed[v]) sz[u] += calc_size(v, u);
        return sz[u];
    }

    int find_centroid(int u, int p, int total) {
        for (int v : adj[u]) if (v != p && !removed[v] && sz[v] * 2 > total) return find_centroid(v, u, total);
        return u;
    }

    void add_dist(int u, int p, int c, int d) {
        anc[u].push_back({c, d});
        for (int v : adj[u]) if (v != p && !removed[v]) add_dist(v, u, c, d + 1);
    }

    void build(int u) {
        int c = find_centroid(u, -1, calc_size(u, -1));
        add_dist(c, -1, c, 0);
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
//   rooted(adj, root)   id of the rooted tree: equal ids means isomorphic, O(n log n)
//   centers(adj)        the 1 or 2 centers of the tree, O(n)
//   unrooted(adj)       id of the unrooted tree: equal ids means isomorphic, O(n log n)
struct TreeCanon {
    map<vector<int>, int> ids;

    int rooted(const vector<vector<int>> &adj, int root) {
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
        return id[root];
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
        for (int c : centers(adj)) res = min(res, rooted(adj, c));
        return res;
    }
};

// rerooting DP example: sum of distances from each vertex to all others, T = {sum of distances, vertex count}
// id = empty merge, merge combines children (need not be invertible), lift moves a value across edge from -> to,
// finish adds vertex v to the merged children; use from and to to look up edge weights
struct SumDist {
    using T = pll;
    static T id() { return {0, 0}; }
    static T merge(const T &a, const T &b) { return {a.first + b.first, a.second + b.second}; }
    static T lift(const T &x, int, int) { return {x.first + x.second, x.second}; }
    static T finish(const T &x, int) { return {x.first, x.second + 1}; }
};

// answer of a tree DP for every choice of root; returns ans[v] for each v, S shaped like SumDist above, O(n)
template <class S>
vector<typename S::T> rerooting(const vector<vector<int>> &adj) {
    using T = typename S::T;
    int n = adj.size();
    vector<int> order{0}, par(n, -1);
    for (int i = 0; i < (int)order.size(); i++) {
        for (int v : adj[order[i]]) {
            if (v == par[order[i]]) continue;
            par[v] = order[i];
            order.push_back(v);
        }
    }
    vector<T> down(n, S::id()), up(n, S::id()), ans(n);  // up[v] = what v's parent contributes to v
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        T cur = S::id();
        for (int u : adj[v]) if (u != par[v]) cur = S::merge(cur, S::lift(down[u], u, v));
        down[v] = S::finish(cur, v);
    }
    for (int v : order) {
        int k = adj[v].size();
        vector<T> pre(k + 1, S::id()), suf(k + 1, S::id());  // allows merge to have no inverse
        auto value = [&](int u) { return u == par[v] ? up[v] : S::lift(down[u], u, v); };
        for (int i = 0; i < k; i++) pre[i + 1] = S::merge(pre[i], value(adj[v][i]));
        for (int i = k - 1; i >= 0; i--) suf[i] = S::merge(value(adj[v][i]), suf[i + 1]);
        ans[v] = S::finish(pre[k], v);
        for (int i = 0; i < k; i++) {
            int u = adj[v][i];
            if (u != par[v]) up[u] = S::lift(S::finish(S::merge(pre[i], suf[i + 1]), v), v, u);
        }
    }
    return ans;
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

// virtual tree of the vertices vs, using LCA above; returns {nodes, par}, nodes sorted by DFS order and containing vs and
// all their pairwise LCAs, par[i] = the parent vertex of nodes[i] in the virtual tree (-1 for the first), O(k log k)
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

// link-cut tree: a forest under link and cut with path sum queries, 0-indexed; node values start at 0
//   LinkCutTree(n)    n isolated vertices, O(n)
//   make_root(x)      internal: make internal vertex x the root of its tree, O(log n) amortized
//   access(x)         internal: expose the root-to-x path, returns the last jump point, O(log n) amortized
//   connected(u, v)   true if u and v are in the same tree, O(log n) amortized
//   link(u, v)        add the edge u - v; false if they were already connected, O(log n) amortized
//   cut(u, v)         remove the edge u - v; false if it doesn't exist, O(log n) amortized
//   set(v, x)         set the value of v, O(log n) amortized
//   path_sum(u, v)    sum of the values on the path u - v; re-roots the tree at u; u and v must be connected, O(log n) amortized
//   reroot(v)         make v the root of its tree, O(log n) amortized
//   lca(u, v)         lowest common ancestor for the current root; u and v must be connected, O(log n) amortized
struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        ll val = 0, sum = 0;
        bool rev = false;
    };
    vector<Node> t;  // internal vertices are 1..n and 0 is null
    vector<int> path;

    LinkCutTree(int n = 0): t(n + 1) {}

    bool is_root(int x) const {
        int p = t[x].p;
        return !p || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void pull(int x) { t[x].sum = t[t[x].ch[0]].sum + t[x].val + t[t[x].ch[1]].sum; }

    void flip(int x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        t[x].rev = !t[x].rev;
    }

    void push(int x) {
        if (!t[x].rev) return;
        flip(t[x].ch[0]);
        flip(t[x].ch[1]);
        t[x].rev = false;
    }

    void rotate(int x) {
        int p = t[x].p, g = t[p].p, d = t[p].ch[1] == x, c = t[x].ch[!d];
        if (!is_root(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g;
        t[p].ch[d] = c;
        if (c) t[c].p = p;
        t[x].ch[!d] = p;
        t[p].p = x;
        pull(p);
        pull(x);
    }

    void splay(int x) {
        path.clear();
        for (int y = x; ; y = t[y].p) {
            path.push_back(y);
            if (is_root(y)) break;
        }
        for (int i = (int)path.size() - 1; i >= 0; i--) push(path[i]);
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) rotate((t[p].ch[1] == x) == (t[g].ch[1] == p) ? p : x);
            rotate(x);
        }
    }

    int access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pull(y);
            last = y;
        }
        splay(x);
        return last;
    }

    void make_root(int x) {
        access(x);
        flip(x);
    }

    int find_root(int x) {
        access(x);
        while (true) {
            push(x);
            if (!t[x].ch[0]) break;
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) { return find_root(u + 1) == find_root(v + 1); }

    bool link(int u, int v) {
        if (connected(u, v)) return false;
        make_root(u + 1);
        t[u + 1].p = v + 1;
        return true;
    }

    bool cut(int u, int v) {
        u++;
        v++;
        if (u == v || find_root(u) != find_root(v)) return false;
        make_root(u);
        access(v);
        push(u);
        if (t[v].ch[0] != u || t[u].ch[1]) return false;
        t[v].ch[0] = 0;
        t[u].p = 0;
        pull(v);
        return true;
    }

    void set(int v, ll x) {
        v++;
        access(v);
        t[v].val = x;
        pull(v);
    }

    ll path_sum(int u, int v) {
        make_root(u + 1);
        access(v + 1);
        return t[v + 1].sum;
    }

    void reroot(int v) { make_root(v + 1); }

    int lca(int u, int v) {
        access(u + 1);
        return access(v + 1) - 1;
    }
};
