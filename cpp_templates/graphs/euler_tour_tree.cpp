// Contents
//   EulerTourTree   a forest under link and cut, with component sums and subtree add / subtree sum, 0-indexed

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// Euler tour tree: a forest under link and cut, with component sums and subtree add / subtree sum, 0-indexed
// each tree is stored as its Euler tour in a treap: a node per vertex (holding its value) and one per direction
// of each edge, so a subtree is a contiguous range of the tour. node v + 1 is vertex v, 0 is null
// unlike LinkCutTree it can add to a whole subtree, but it has no path queries; all costs are expected (treap)
//   EulerTourTree(n)       n isolated vertices with value 0, O(n)
//   connected(u, v)        true if u and v are in the same tree, O(log n)
//   link(u, v)             add the edge u - v; u and v must be in different trees, O(log n)
//   cut(u, v)              remove the edge u - v; it must exist, O(log n)
//   add(v, x)              add x to the value of v, O(log n)
//   component_sum(v)       sum of the values in v's tree, O(log n)
//   subtree_add(v, p, x)   add x to every value in the subtree of v when its neighbour p is its parent, O(log n)
//   subtree_sum(v, p)      sum of the values in that subtree, O(log n)
struct EulerTourTree {
    struct Node {
        int l = 0, r = 0, p = 0, sz = 1, cnt = 0;  // cnt = number of vertex nodes in the treap subtree
        unsigned pri = 0;
        bool vert = false;
        ll val = 0, sum = 0, lazy = 0;  // lazy = amount still to add to every vertex below
    };
    vector<Node> t;
    map<pair<int, int>, int> edge;  // directed edge (u, v) -> its node
    mt19937 rng{(unsigned)chrono::steady_clock::now().time_since_epoch().count()};

    EulerTourTree(int n = 0): t(1) {
        t[0].sz = 0;
        for (int i = 0; i < n; i++) make(true);
    }

    int make(bool vert) {
        t.emplace_back();
        t.back().pri = rng();
        t.back().vert = vert;
        t.back().cnt = vert;
        return t.size() - 1;
    }

    void apply(int x, ll d) {
        if (!x) return;
        if (t[x].vert) t[x].val += d;
        t[x].sum += d * t[x].cnt;
        t[x].lazy += d;
    }

    void push(int x) {
        if (!t[x].lazy) return;
        apply(t[x].l, t[x].lazy);
        apply(t[x].r, t[x].lazy);
        t[x].lazy = 0;
    }

    void pull(int x) {
        int l = t[x].l, r = t[x].r;
        t[x].sz = 1 + t[l].sz + t[r].sz;
        t[x].cnt = t[x].vert + t[l].cnt + t[r].cnt;
        t[x].sum = t[x].val + t[l].sum + t[r].sum;
        if (l) t[l].p = x;
        if (r) t[r].p = x;
    }

    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (t[a].pri > t[b].pri) {
            push(a);
            t[a].r = merge(t[a].r, b);
            pull(a);
            return a;
        }
        push(b);
        t[b].l = merge(a, t[b].l);
        pull(b);
        return b;
    }

    pair<int, int> split(int x, int k) {  // {first k nodes of the tour, the rest}; parents of the results are stale
        if (!x) return {0, 0};
        push(x);
        if (t[t[x].l].sz >= k) {
            auto [a, b] = split(t[x].l, k);
            t[x].l = b;
            pull(x);
            return {a, x};
        }
        auto [a, b] = split(t[x].r, k - t[t[x].l].sz - 1);
        t[x].r = a;
        pull(x);
        return {x, b};
    }

    int join(int a, int b) {  // merge, then mark the result as a root
        int r = merge(a, b);
        t[r].p = 0;
        return r;
    }

    pair<int, int> cut_at(int x, int k) {  // split, then mark both parts as roots
        auto [a, b] = split(x, k);
        t[a].p = t[b].p = 0;
        return {a, b};
    }

    int root(int x) const {
        while (t[x].p) x = t[x].p;
        return x;
    }

    int index(int x) const {  // position of node x in its tour (no reversals, so lazy tags don't matter)
        int k = t[t[x].l].sz;
        for (int p = t[x].p; p; x = p, p = t[p].p) if (t[p].r == x) k += t[t[p].l].sz + 1;
        return k;
    }

    void reroot(int v) {  // rotate v's tour so that it starts at v
        auto [a, b] = cut_at(root(v + 1), index(v + 1));
        join(b, a);
    }

    template <class F>
    void range(int x, int lo, int hi, F f) {  // call f on the treap of positions [lo, hi) of x's tour
        auto [a, rest] = cut_at(root(x), lo);
        auto [m, c] = cut_at(rest, hi - lo);
        f(m);
        join(join(a, m), c);
    }

    bool connected(int u, int v) const { return root(u + 1) == root(v + 1); }

    void link(int u, int v) {
        reroot(u);
        reroot(v);
        int uv = make(false), vu = make(false);
        edge[{u, v}] = uv;
        edge[{v, u}] = vu;
        join(join(join(root(u + 1), uv), root(v + 1)), vu);
    }

    void cut(int u, int v) {
        int uv = edge[{u, v}], vu = edge[{v, u}];
        edge.erase({u, v});
        edge.erase({v, u});
        int i = index(uv), j = index(vu);
        if (i > j) swap(i, j);
        auto [a, rest] = cut_at(root(uv), i);
        auto [mid, c] = cut_at(rest, j - i + 1);  // the edge node, the subtree, the other edge node
        cut_at(cut_at(mid, j - i).first, 1);  // drop both edge nodes, so the subtree is a tour of its own
        join(a, c);
    }

    void add(int v, ll x) {
        int k = index(v + 1);
        range(v + 1, k, k + 1, [&](int m) { apply(m, x); });
    }

    ll component_sum(int v) const { return t[root(v + 1)].sum; }

    template <class F>
    void subtree(int v, int p, F f) {  // after rerooting at p, the subtree of v lies strictly between p->v and v->p
        reroot(p);
        int i = index(edge[{p, v}]), j = index(edge[{v, p}]);
        range(v + 1, i + 1, j, f);
    }

    void subtree_add(int v, int p, ll x) {
        subtree(v, p, [&](int m) { apply(m, x); });
    }

    ll subtree_sum(int v, int p) {
        ll res = 0;
        subtree(v, p, [&](int m) { res = t[m].sum; });
        return res;
    }
};
