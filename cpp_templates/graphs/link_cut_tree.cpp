// Contents
//   LinkCutTree     link-cut tree: a forest under link and cut with path and subtree sum queries, 0-indexed
//   LinkCutPath     link-cut tree with path folds of any monoid (op need not commute), 0-indexed
//   IncrementalMSF  incremental minimum spanning forest: add edges one at a time, O(log(n + m)) amortized each

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// link-cut tree: a forest under link and cut with path and subtree sum queries, 0-indexed; node values start at 0
// sum is over the splay subtree (a path); sub also counts vir, the sums of the virtual (non-preferred) children
//   LinkCutTree(n)    n isolated vertices, O(n)
//   make_root(x)      internal: make internal vertex x the root of its tree, O(log n) amortized
//   access(x)         internal: expose the root-to-x path, returns the last jump point, O(log n) amortized
//   connected(u, v)   true if u and v are in the same tree, O(log n) amortized
//   link(u, v)        add the edge u - v; false if they were already connected, O(log n) amortized
//   cut(u, v)         remove the edge u - v; false if it doesn't exist, O(log n) amortized
//   set(v, x)         set the value of v, O(log n) amortized
//   path_sum(u, v)    sum of the values on the path u - v; re-roots the tree at u;
//                     u and v must be connected, O(log n) amortized
//   subtree_sum(v, p) sum of the values in the subtree of v when the tree is rooted at p (p = v: the whole tree);
//                     re-roots the tree at p; v and p must be connected, O(log n) amortized
//   reroot(v)         make v the root of its tree, O(log n) amortized
//   lca(u, v)         lowest common ancestor for the current root; u and v must be connected, O(log n) amortized
struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        ll val = 0, sum = 0, vir = 0, sub = 0;
        bool rev = false;
    };
    vector<Node> t;  // internal vertices are 1..n and 0 is null
    vector<int> path;

    LinkCutTree(int n = 0): t(n + 1) {}

    bool is_root(int x) const {
        int p = t[x].p;
        return !p || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void pull(int x) {
        int l = t[x].ch[0], r = t[x].ch[1];
        t[x].sum = t[l].sum + t[x].val + t[r].sum;
        t[x].sub = t[l].sub + t[x].val + t[r].sub + t[x].vir;
    }

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
            t[y].vir += t[t[y].ch[1]].sub - t[last].sub;  // the old preferred child becomes virtual
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
        access(v + 1);
        t[u + 1].p = v + 1;
        t[v + 1].vir += t[u + 1].sub;
        pull(v + 1);
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

    ll subtree_sum(int v, int p) {
        make_root(p + 1);
        access(v + 1);
        return t[v + 1].val + t[v + 1].vir;
    }

    void reroot(int v) { make_root(v + 1); }

    int lca(int u, int v) {
        access(u + 1);
        return access(v + 1) - 1;
    }
};

// link-cut tree for path folds of any monoid M (like the ones in monoids.cpp; op need not commute), 0-indexed
// each splay node keeps the fold of its subtree in path order and reversed, so re-rooting just swaps the two
//   LinkCutPath(a)   isolated vertices with values a, O(n)
//   link(u, v)       add the edge u - v; u and v must not be connected, O(log n) amortized
//   cut(u, v)        remove the edge u - v, which must exist, O(log n) amortized
//   set(v, x)        set the value of v, O(log n) amortized
//   fold(u, v)       op of the values on the path from u to v, in that order; u and v connected, O(log n) amortized
template <class M>
struct LinkCutPath {
    using T = typename M::T;
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        bool rev = false;
        T val, sum, rsum;
    };
    vector<Node> t;  // internal vertices are 1..n and 0 is null

    LinkCutPath(const vector<T> &a): t(a.size() + 1) {
        t[0].val = t[0].sum = t[0].rsum = M::id();
        for (size_t i = 0; i < a.size(); i++) t[i + 1].val = t[i + 1].sum = t[i + 1].rsum = a[i];
    }

    bool is_root(int x) const {
        int p = t[x].p;
        return !p || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void pull(int x) {
        int l = t[x].ch[0], r = t[x].ch[1];
        t[x].sum = M::op(M::op(t[l].sum, t[x].val), t[r].sum);
        t[x].rsum = M::op(M::op(t[r].rsum, t[x].val), t[l].rsum);
    }

    void flip(int x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        swap(t[x].sum, t[x].rsum);
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
        vector<int> path{x};
        for (int y = x; !is_root(y); y = t[y].p) path.push_back(t[y].p);
        for (int i = (int)path.size() - 1; i >= 0; i--) push(path[i]);
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) rotate((t[p].ch[1] == x) == (t[g].ch[1] == p) ? p : x);
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = x, last = 0; y; last = y, y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pull(y);
        }
        splay(x);
    }

    void make_root(int x) {
        access(x);
        flip(x);
    }

    void link(int u, int v) {
        make_root(u + 1);
        t[u + 1].p = v + 1;
    }

    void cut(int u, int v) {
        make_root(u + 1);
        access(v + 1);
        t[v + 1].ch[0] = t[u + 1].p = 0;
        pull(v + 1);
    }

    void set(int v, const T &x) {
        access(v + 1);
        t[v + 1].val = x;
        pull(v + 1);
    }

    T fold(int u, int v) {
        make_root(u + 1);
        access(v + 1);
        return t[v + 1].sum;
    }
};

// incremental minimum spanning forest: edges arrive one at a time and the forest stays minimum, 0-indexed vertices,
// edges numbered 0, 1, ... in the order added; for each new edge u - v, if u and v are connected the heaviest edge on
// the forest path u - v leaves if it is heavier than the new one, else the new edge is dropped
// a link-cut tree with a node per edge (between its two endpoints) keeps the argmax of the path's edge weights;
// components only merge, so a DSU answers connectivity
//   IncrementalMSF(n)    n isolated vertices, O(n)
//   add_edge(u, v, w)    add the edge, returns the id of the edge that is not in the forest afterwards: the new
//                        edge itself (a loop, or no heavier edge on the path), the edge it replaced, or -1 if it
//                        joined two trees, O(log(n + m)) amortized
//   total                sum of the forest's edge weights
//   in_forest[id]        true if edge id is in the forest
struct IncrementalMSF {
    struct Node {
        int ch[2] = {0, 0}, p = 0, mx = 0;  // mx = the node with the largest val in the splay subtree
        ll val = LLONG_MIN;
        bool rev = false;
    };
    int n;
    ll total = 0;
    vector<Node> t;  // vertices are 1..n, edge i is n + 1 + i, 0 is null
    vector<array<int, 2>> ends;
    vector<char> in_forest;
    vector<int> dsu, path;

    IncrementalMSF(int n): n(n), t(n + 1), dsu(n + 1) {
        for (int i = 1; i <= n; i++) t[i].mx = i;
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find_set(int x) {
        while (dsu[x] != x) x = dsu[x] = dsu[dsu[x]];
        return x;
    }

    bool is_root(int x) const { return t[t[x].p].ch[0] != x && t[t[x].p].ch[1] != x; }

    void pull(int x) {
        t[x].mx = x;
        for (int c : t[x].ch) if (c && t[t[c].mx].val > t[t[x].mx].val) t[x].mx = t[c].mx;
    }

    void flip(int x) {
        if (x) swap(t[x].ch[0], t[x].ch[1]), t[x].rev ^= 1;
    }

    void push(int x) {
        if (t[x].rev) flip(t[x].ch[0]), flip(t[x].ch[1]), t[x].rev = false;
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
        path.assign(1, x);
        for (int y = x; !is_root(y); y = t[y].p) path.push_back(t[y].p);
        for (int i = (int)path.size() - 1; i >= 0; i--) push(path[i]);
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) rotate((t[p].ch[1] == x) == (t[g].ch[1] == p) ? p : x);
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = x, last = 0; y; last = y, y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            pull(y);
        }
        splay(x);
    }

    void make_root(int x) {
        access(x);
        flip(x);
    }

    void link(int x, int y) {
        make_root(x);
        t[x].p = y;
    }

    void cut(int x, int y) {
        make_root(x);
        access(y);
        t[y].ch[0] = t[x].p = 0;
        pull(y);
    }

    int add_edge(int u, int v, ll w) {
        int id = ends.size(), e = n + 1 + id;
        u++, v++;
        ends.push_back({u, v});
        in_forest.push_back(false);
        t.push_back(Node());
        t[e].val = w, t[e].mx = e;
        int out = -1;
        if (u == v) return id;
        if (find_set(u) == find_set(v)) {
            make_root(u);
            access(v);
            int x = t[v].mx;  // heaviest edge on the path u - v
            if (t[x].val <= w) return id;
            out = x - n - 1;
            cut(ends[out][0], x);
            cut(x, ends[out][1]);
            in_forest[out] = false;
            total -= t[x].val;
        } else {
            dsu[find_set(u)] = find_set(v);
        }
        link(u, e);
        link(e, v);
        in_forest[id] = true;
        total += w;
        return out;
    }
};
