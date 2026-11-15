#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// example monoid (sum): id() is the identity, op must be associative (same shape as segment_tree.cpp)
struct Monoid {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
};

// persistent segment tree, point update, query on [l, r); version 0 is all identity or the built array
// each update makes a new version and leaves the old ones unchanged
// PersistentSegTree<M>: works with any monoid M shaped like Monoid above
//   PersistentSegTree(n)    version 0 is n identity elements, O(1)
//   PersistentSegTree(a)    version 0 is a, O(n)
//   set(ver, p, v)          a[p] = v on a copy of ver, returns the new version, O(log n) time and memory
//   update(ver, p, v)       a[p] = op(a[p], v) on a copy of ver, returns the new version, O(log n) time and memory
//   get(ver, p)             a[p] in ver, O(log n)
//   query(ver, l, r)        op over [l, r) in ver, O(log n)
template <class M>
struct PersistentSegTree {
    using T = typename M::T;
    struct Node { int l, r; T val; };
    int n;
    vector<Node> t;  // t[0] is the empty node: identity value, children are itself
    vector<int> roots;

    PersistentSegTree(int n = 0): n(n), t(1, Node{0, 0, M::id()}), roots(1, 0) {}

    PersistentSegTree(const vector<T> &a): PersistentSegTree((int)a.size()) {
        if (n) roots[0] = build(a, 0, n);
    }

    int build(const vector<T> &a, int lo, int hi) {
        if (hi - lo == 1) {
            t.push_back({0, 0, a[lo]});
            return t.size() - 1;
        }
        int mid = (lo + hi) / 2;
        int l = build(a, lo, mid), r = build(a, mid, hi);
        t.push_back({l, r, M::op(t[l].val, t[r].val)});
        return t.size() - 1;
    }

    int set(int ver, int p, const T &v) {
        roots.push_back(set_node(roots[ver], 0, n, p, v));
        return roots.size() - 1;
    }

    int set_node(int x, int lo, int hi, int p, const T &v) {
        Node cur = t[x];
        if (hi - lo == 1) {
            cur.val = v;
        } else {
            int mid = (lo + hi) / 2;
            if (p < mid) cur.l = set_node(cur.l, lo, mid, p, v);
            else cur.r = set_node(cur.r, mid, hi, p, v);
            cur.val = M::op(t[cur.l].val, t[cur.r].val);
        }
        t.push_back(cur);
        return t.size() - 1;
    }

    int update(int ver, int p, const T &v) { return set(ver, p, M::op(get(ver, p), v)); }

    T get(int ver, int p) const {
        int x = roots[ver], lo = 0, hi = n;
        while (x && hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (p < mid) x = t[x].l, hi = mid;
            else x = t[x].r, lo = mid;
        }
        return t[x].val;
    }

    T query(int ver, int l, int r) const { return query_node(roots[ver], 0, n, l, r); }

    T query_node(int x, int lo, int hi, int l, int r) const {
        if (!x || r <= lo || hi <= l) return M::id();
        if (l <= lo && hi <= r) return t[x].val;
        int mid = (lo + hi) / 2;
        return M::op(query_node(t[x].l, lo, mid, l, r), query_node(t[x].r, mid, hi, l, r));
    }
};

// example lazy spec (range add, range sum): T = {sum, length}, F = amount added (same shape as segment_tree.cpp)
// build from leaves {x, 1}, since identity leaves {0, 0} have length 0
struct Spec {
    using T = pll;
    using F = ll;
    static T id() { return {0, 0}; }
    static T op(const T &a, const T &b) { return {a.first + b.first, a.second + b.second}; }
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return {x.first + f * x.second, x.second}; }
    static F compose(const F &f, const F &g) { return f + g; }  // f after g
};

// persistent lazy segment tree, range update and query on [l, r); version 0 is the built array
// a node's tag is always newer than everything below it, so queries apply tags on the way up and allocate nothing;
// updates hand pending tags down to fresh copies of the children, so F does not need to be commutative
// PersistentLazySegTree<S>: works with any S shaped like Spec above
//   PersistentLazySegTree(n)    version 0 is n identity elements, O(n)
//   PersistentLazySegTree(a)    version 0 is a, O(n)
//   update(ver, l, r, f)        apply f to every element of [l, r) on a copy of ver, returns the new version, O(log n) time and memory
//   get(ver, p)                 a[p] in ver, O(log n)
//   query(ver, l, r)            op over [l, r) in ver, O(log n)
template <class S>
struct PersistentLazySegTree {
    using T = typename S::T;
    using F = typename S::F;
    struct Node { int l, r; T val; F lz; };
    int n;
    vector<Node> t;  // t[0] is a placeholder, used only as the root when n = 0
    vector<int> roots;

    PersistentLazySegTree(int n = 0): PersistentLazySegTree(vector<T>(n, S::id())) {}

    PersistentLazySegTree(const vector<T> &a): n(a.size()), t(1, Node{0, 0, S::id(), S::fid()}), roots(1, 0) {
        if (n) roots[0] = build(a, 0, n);
    }

    int build(const vector<T> &a, int lo, int hi) {
        if (hi - lo == 1) {
            t.push_back({0, 0, a[lo], S::fid()});
            return t.size() - 1;
        }
        int mid = (lo + hi) / 2;
        int l = build(a, lo, mid), r = build(a, mid, hi);
        t.push_back({l, r, S::op(t[l].val, t[r].val), S::fid()});
        return t.size() - 1;
    }

    int applied(int x, const F &f) {  // a copy of node x with f applied to its whole subtree
        Node cur = t[x];
        cur.val = S::apply(f, cur.val);
        cur.lz = S::compose(f, cur.lz);
        t.push_back(cur);
        return t.size() - 1;
    }

    int update(int ver, int l, int r, const F &f) {
        roots.push_back(l < r && n ? update_node(roots[ver], 0, n, l, r, f, S::fid()) : roots[ver]);
        return roots.size() - 1;
    }

    // g is the pending tag from the ancestors, which is newer than anything stored in x's subtree
    int update_node(int x, int lo, int hi, int l, int r, const F &f, const F &g) {
        if (r <= lo || hi <= l) return applied(x, g);
        if (l <= lo && hi <= r) return applied(x, S::compose(f, g));
        Node cur = t[x];
        F h = S::compose(g, cur.lz);
        int mid = (lo + hi) / 2;
        cur.l = update_node(cur.l, lo, mid, l, r, f, h);
        cur.r = update_node(cur.r, mid, hi, l, r, f, h);
        cur.val = S::op(t[cur.l].val, t[cur.r].val);
        cur.lz = S::fid();
        t.push_back(cur);
        return t.size() - 1;
    }

    T get(int ver, int p) const { return query(ver, p, p + 1); }

    T query(int ver, int l, int r) const { return query_node(roots[ver], 0, n, l, r); }

    T query_node(int x, int lo, int hi, int l, int r) const {
        if (r <= lo || hi <= l) return S::id();
        if (l <= lo && hi <= r) return t[x].val;
        int mid = (lo + hi) / 2;
        return S::apply(t[x].lz, S::op(query_node(t[x].l, lo, mid, l, r), query_node(t[x].r, mid, hi, l, r)));
    }
};

// counts values <= x in any subarray, online; values can be any integers
//   LeqCounter(a)      build from a, O(n log n)
//   count(l, r, x)     number of i in [l, r) with a[i] <= x, O(log n)
struct LeqCounter {
    struct Count {
        using T = int;
        static T id() { return 0; }
        static T op(const T &a, const T &b) { return a + b; }
    };
    vector<ll> sorted_vals;
    PersistentSegTree<Count> tree;

    LeqCounter(const vector<ll> &a): tree((int)a.size()) {
        int n = a.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) { return a[i] < a[j]; });
        for (int i : order) {
            sorted_vals.push_back(a[i]);
            tree.set(tree.roots.size() - 1, i, 1);
        }
    }

    int count(int l, int r, ll x) const {
        int ver = upper_bound(sorted_vals.begin(), sorted_vals.end(), x) - sorted_vals.begin();
        return tree.query(ver, l, r);
    }
};

// counts distinct values in any subarray, online; uses LeqCounter above
//   UniqueCounter(a)    build from a, O(n log n)
//   count(l, r)         number of distinct values in a[l..r), O(log n)
struct UniqueCounter {
    LeqCounter counter;

    static vector<ll> previous(const vector<ll> &a) {  // 1-indexed position of the previous equal value, 0 if none
        map<ll, int> last;
        vector<ll> b(a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            b[i] = last[a[i]];
            last[a[i]] = i + 1;
        }
        return b;
    }

    UniqueCounter(const vector<ll> &a): counter(previous(a)) {}

    int count(int l, int r) const { return counter.count(l, r, l); }  // a[i] is new if its previous copy is before l
};
