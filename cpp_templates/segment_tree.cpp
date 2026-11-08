#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// iterative segment tree, point update, query on [l, r)
// example monoid (sum): id() is the identity, op must be associative
struct Monoid {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
};

// SegTree<M>: works with any monoid M shaped like Monoid above
//   SegTree(n)    n identity elements, O(n)
//   SegTree(a)    build from a, O(n)
//   set(p, v)     a[p] = v, O(log n)
//   get(p)        a[p], O(1)
//   query(l, r)   op over [l, r), O(log n)
template <class M>
struct SegTree {
    using T = typename M::T;
    int n;
    vector<T> t;

    SegTree(int n = 0): n(n), t(2 * n, M::id()) {}

    SegTree(const vector<T> &a): n(a.size()), t(2 * a.size(), M::id()) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = M::op(t[2 * i], t[2 * i + 1]);
    }

    void set(int p, T v) {
        for (t[p += n] = v; p > 1; p >>= 1)
            t[p >> 1] = M::op(t[p & ~1], t[p | 1]);
    }

    T get(int p) const { return t[p + n]; }

    T query(int l, int r) const {
        T L = M::id(), R = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = M::op(L, t[l++]);
            if (r & 1) R = M::op(t[--r], R);
        }
        return M::op(L, R);
    }
};

// lazy segment tree (iterative), range update and query on [l, r)
// example: range add, range sum; T = {sum, length}, F = amount added
// build from leaves {x, 1}, since the default leaves {0, 0} have length 0
struct Spec {
    using T = pll;
    using F = ll;
    static T id() { return {0, 0}; }
    static T op(const T &a, const T &b) { return {a.first + b.first, a.second + b.second}; }
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return {x.first + f * x.second, x.second}; }
    static F compose(const F &f, const F &g) { return f + g; }
};

// LazySegTree<S>: works with any S shaped like Spec above
//   LazySegTree(n)    n identity elements, O(n)
//   LazySegTree(a)    build from a, O(n)
//   pull(k)           recompute node k from its children, O(1)
//   all_apply(k, f)   apply f to node k and record it as a pending tag, O(1)
//   push(k)           push node k's pending tag down to its children, O(1)
//   set(p, v)         a[p] = v, O(log n)
//   get(p)            a[p], O(log n)
//   query(l, r)       op over [l, r), O(log n)
//   update(l, r, f)   apply f to every element in [l, r), O(log n)
template <class S>
struct LazySegTree {
    using T = typename S::T;
    using F = typename S::F;
    int n, sz, lg;
    vector<T> d;
    vector<F> lz;

    LazySegTree(int n = 0): LazySegTree(vector<T>(n, S::id())) {}

    LazySegTree(const vector<T> &a): n(a.size()) {
        sz = 1; lg = 0;
        while (sz < n) sz <<= 1, lg++;
        d.assign(2 * sz, S::id());
        lz.assign(sz, S::fid());
        for (int i = 0; i < n; i++) d[sz + i] = a[i];
        for (int i = sz - 1; i >= 1; i--) pull(i);
    }

    void pull(int k) { d[k] = S::op(d[2 * k], d[2 * k + 1]); }

    void all_apply(int k, const F &f) {
        d[k] = S::apply(f, d[k]);
        if (k < sz) lz[k] = S::compose(f, lz[k]);
    }

    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = S::fid();
    }

    void set(int p, T v) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = v;
        for (int i = 1; i <= lg; i++) pull(p >> i);
    }

    T get(int p) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }

    T query(int l, int r) {
        if (l >= r) return S::id();
        l += sz; r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        T L = S::id(), R = S::id();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = S::op(L, d[l++]);
            if (r & 1) R = S::op(d[--r], R);
        }
        return S::op(L, R);
    }

    void update(int l, int r, const F &f) {
        if (l >= r) return;
        l += sz; r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
        }
        l = l2; r = r2;
        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) pull(l >> i);
            if (((r >> i) << i) != r) pull((r - 1) >> i);
        }
    }
};

// 2D segment tree (iterative), point update, query on [r1, r2] x [c1, c2] (uses Monoid above)
//   SegTree2D(n, m)         n x m grid of identity elements, O(nm)
//   SegTree2D(a)            build from grid a, O(nm)
//   set(x, y, v)            a[x][y] = v, O(log n log m)
//   get(x, y)               a[x][y], O(1)
//   row_query(i, l, r)      op over columns [l, r) of tree row i, O(log m)
//   query(r1, c1, r2, c2)   op over the rectangle [r1, r2] x [c1, c2] (inclusive), O(log n log m)
template <class M>
struct SegTree2D {
    using T = typename M::T;
    int n, m;
    vector<vector<T>> t;

    SegTree2D(int n = 0, int m = 0): n(n), m(m), t(2 * n, vector<T>(2 * m, M::id())) {}

    SegTree2D(const vector<vector<T>> &a): SegTree2D(a.size(), a.empty() ? 0 : a[0].size()) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) t[n + i][m + j] = a[i][j];
        for (int i = n; i < 2 * n; i++)
            for (int j = m - 1; j > 0; j--) t[i][j] = M::op(t[i][2 * j], t[i][2 * j + 1]);
        for (int i = n - 1; i > 0; i--)
            for (int j = 1; j < 2 * m; j++) t[i][j] = M::op(t[2 * i][j], t[2 * i + 1][j]);
    }

    void set(int x, int y, T v) {
        x += n; y += m;
        t[x][y] = v;
        for (int j = y; j > 1; j >>= 1) t[x][j >> 1] = M::op(t[x][j & ~1], t[x][j | 1]);
        for (int i = x; i > 1; i >>= 1) {
            t[i >> 1][y] = M::op(t[i & ~1][y], t[i | 1][y]);
            for (int j = y; j > 1; j >>= 1)
                t[i >> 1][j >> 1] = M::op(t[i >> 1][j & ~1], t[i >> 1][j | 1]);
        }
    }

    T get(int x, int y) const { return t[x + n][y + m]; }

    T row_query(int i, int l, int r) const {
        T res = M::id();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = M::op(res, t[i][l++]);
            if (r & 1) res = M::op(res, t[i][--r]);
        }
        return res;
    }

    T query(int r1, int c1, int r2, int c2) const {
        T res = M::id();
        for (int i = r1 + n, k = r2 + 1 + n; i < k; i >>= 1, k >>= 1) {
            if (i & 1) res = M::op(res, row_query(i++, c1, c2 + 1));
            if (k & 1) res = M::op(res, row_query(--k, c1, c2 + 1));
        }
        return res;
    }
};

// implicit segment tree on any integer range [lo, hi), nodes are created as needed (uses a monoid like Monoid above)
// Q = number of updates
//   DynamicSegTree(lo, hi)   all identity elements, O(1)
//   set(p, v)                a[p] = v, O(log(hi - lo)) time and memory
//   get(p)                   a[p], O(log(hi - lo))
//   query(l, r)              op over [l, r), O(log(hi - lo))
template <class M>
struct DynamicSegTree {
    using T = typename M::T;
    struct Node { T val; int l, r; };
    ll lo, hi;
    vector<Node> t;  // t[0] is the root; a child index of 0 means no child

    DynamicSegTree(ll lo, ll hi): lo(lo), hi(hi), t(1, Node{M::id(), 0, 0}) {}

    T val(int x) const { return x ? t[x].val : M::id(); }

    void set(ll p, const T &v) { set_node(0, lo, hi, p, v); }

    void set_node(int x, ll a, ll b, ll p, const T &v) {
        if (b - a == 1) {
            t[x].val = v;
            return;
        }
        ll m = a + (b - a) / 2;
        int &slot_check = p < m ? t[x].l : t[x].r;
        if (!slot_check) {
            int id = t.size();
            slot_check = id;
            t.push_back({M::id(), 0, 0});  // invalidates slot_check, which isn't used again
        }
        int child = p < m ? t[x].l : t[x].r;
        if (p < m) set_node(child, a, m, p, v);
        else set_node(child, m, b, p, v);
        t[x].val = M::op(val(t[x].l), val(t[x].r));
    }

    T get(ll p) const { return query(p, p + 1); }

    T query(ll l, ll r) const { return query_node(0, lo, hi, l, r); }

    T query_node(int x, ll a, ll b, ll l, ll r) const {
        if (r <= a || b <= l || (x == 0 && (a != lo || b != hi))) return M::id();
        if (l <= a && b <= r) return t[x].val;
        ll m = a + (b - a) / 2;
        return M::op(query_node(t[x].l, a, m, l, r), query_node(t[x].r, m, b, l, r));
    }
};

// merge sort tree: static counting of values in a range, online
//   MergeSortTree(a)          build from a, O(n log n)
//   count_less(l, r, x)       number of i in [l, r) with a[i] < x, O(log^2 n)
//   count_range(l, r, x, y)   number of i in [l, r) with x <= a[i] < y, O(log^2 n)
struct MergeSortTree {
    int n;
    vector<vector<ll>> t;

    MergeSortTree(const vector<ll> &a): n(a.size()), t(2 * a.size()) {
        for (int i = 0; i < n; i++) t[n + i] = {a[i]};
        for (int i = n - 1; i > 0; i--) {
            t[i].resize(t[2 * i].size() + t[2 * i + 1].size());
            merge(t[2 * i].begin(), t[2 * i].end(), t[2 * i + 1].begin(), t[2 * i + 1].end(), t[i].begin());
        }
    }

    int count_less(int l, int r, ll x) const {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res += lower_bound(t[l].begin(), t[l].end(), x) - t[l].begin();
                l++;
            }
            if (r & 1) {
                r--;
                res += lower_bound(t[r].begin(), t[r].end(), x) - t[r].begin();
            }
        }
        return res;
    }

    int count_range(int l, int r, ll x, ll y) const { return count_less(l, r, y) - count_less(l, r, x); }
};

// segment tree beats on [l, r): range chmin, chmax and add with sum, max and min queries
// O((n + q) log n) without add, O((n + q) log^2 n) with add, amortized
//   SegTreeBeats(a)        build from a, O(n)
//   chmin(l, r, x)         a[i] = min(a[i], x) on [l, r)
//   chmax(l, r, x)         a[i] = max(a[i], x) on [l, r)
//   add(l, r, x)           a[i] += x on [l, r)
//   sum(l, r)              sum on [l, r)
//   max_val(l, r)          maximum on [l, r); requires l < r
//   min_val(l, r)          minimum on [l, r); requires l < r
struct SegTreeBeats {
    static constexpr ll LIM = 4e18;
    struct Node { ll mx, mx2, mn, mn2, sum, lazy; int mxc, mnc; };
    int n;
    vector<Node> t;

    SegTreeBeats(const vector<ll> &a): n(a.size()), t(4 * max<size_t>(a.size(), 1)) {
        if (n) build(1, 0, n, a);
    }

    void pull(int k) {
        const Node &a = t[2 * k], &b = t[2 * k + 1];
        Node &c = t[k];
        c.sum = a.sum + b.sum;
        if (a.mx > b.mx) c.mx = a.mx, c.mxc = a.mxc, c.mx2 = max(a.mx2, b.mx);
        else if (a.mx < b.mx) c.mx = b.mx, c.mxc = b.mxc, c.mx2 = max(a.mx, b.mx2);
        else c.mx = a.mx, c.mxc = a.mxc + b.mxc, c.mx2 = max(a.mx2, b.mx2);
        if (a.mn < b.mn) c.mn = a.mn, c.mnc = a.mnc, c.mn2 = min(a.mn2, b.mn);
        else if (a.mn > b.mn) c.mn = b.mn, c.mnc = b.mnc, c.mn2 = min(a.mn, b.mn2);
        else c.mn = a.mn, c.mnc = a.mnc + b.mnc, c.mn2 = min(a.mn2, b.mn2);
    }

    void build(int k, int lo, int hi, const vector<ll> &a) {
        t[k].lazy = 0;
        if (hi - lo == 1) {
            t[k].mx = t[k].mn = t[k].sum = a[lo];
            t[k].mx2 = -LIM;
            t[k].mn2 = LIM;
            t[k].mxc = t[k].mnc = 1;
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * k, lo, mid, a);
        build(2 * k + 1, mid, hi, a);
        pull(k);
    }

    void tag_add(int k, int len, ll x) {
        Node &c = t[k];
        c.mx += x;
        c.mn += x;
        if (c.mx2 != -LIM) c.mx2 += x;
        if (c.mn2 != LIM) c.mn2 += x;
        c.sum += x * len;
        c.lazy += x;
    }

    void tag_chmin(int k, ll x) {  // requires mx2 < x < mx
        Node &c = t[k];
        c.sum += (x - c.mx) * c.mxc;
        if (c.mx == c.mn) c.mn = x;
        else if (c.mx == c.mn2) c.mn2 = x;
        c.mx = x;
    }

    void tag_chmax(int k, ll x) {  // requires mn < x < mn2
        Node &c = t[k];
        c.sum += (x - c.mn) * c.mnc;
        if (c.mn == c.mx) c.mx = x;
        else if (c.mn == c.mx2) c.mx2 = x;
        c.mn = x;
    }

    void push(int k, int lo, int hi) {
        int mid = (lo + hi) / 2;
        if (t[k].lazy) {
            tag_add(2 * k, mid - lo, t[k].lazy);
            tag_add(2 * k + 1, hi - mid, t[k].lazy);
            t[k].lazy = 0;
        }
        for (int c = 2 * k; c <= 2 * k + 1; c++) {
            if (t[c].mx > t[k].mx) tag_chmin(c, t[k].mx);
            if (t[c].mn < t[k].mn) tag_chmax(c, t[k].mn);
        }
    }

    void chmin(int l, int r, ll x) { if (n) chmin(1, 0, n, l, r, x); }

    void chmin(int k, int lo, int hi, int l, int r, ll x) {
        if (r <= lo || hi <= l || t[k].mx <= x) return;
        if (l <= lo && hi <= r && t[k].mx2 < x) {
            tag_chmin(k, x);
            return;
        }
        push(k, lo, hi);
        int mid = (lo + hi) / 2;
        chmin(2 * k, lo, mid, l, r, x);
        chmin(2 * k + 1, mid, hi, l, r, x);
        pull(k);
    }

    void chmax(int l, int r, ll x) { if (n) chmax(1, 0, n, l, r, x); }

    void chmax(int k, int lo, int hi, int l, int r, ll x) {
        if (r <= lo || hi <= l || t[k].mn >= x) return;
        if (l <= lo && hi <= r && t[k].mn2 > x) {
            tag_chmax(k, x);
            return;
        }
        push(k, lo, hi);
        int mid = (lo + hi) / 2;
        chmax(2 * k, lo, mid, l, r, x);
        chmax(2 * k + 1, mid, hi, l, r, x);
        pull(k);
    }

    void add(int l, int r, ll x) { if (n) add(1, 0, n, l, r, x); }

    void add(int k, int lo, int hi, int l, int r, ll x) {
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) {
            tag_add(k, hi - lo, x);
            return;
        }
        push(k, lo, hi);
        int mid = (lo + hi) / 2;
        add(2 * k, lo, mid, l, r, x);
        add(2 * k + 1, mid, hi, l, r, x);
        pull(k);
    }

    // combines f over the nodes covering [l, r), starting from init
    template <class F>
    ll fold(int k, int lo, int hi, int l, int r, ll init, F f) {
        if (r <= lo || hi <= l) return init;
        if (l <= lo && hi <= r) return f(init, k);
        push(k, lo, hi);
        int mid = (lo + hi) / 2;
        return fold(2 * k + 1, mid, hi, l, r, fold(2 * k, lo, mid, l, r, init, f), f);
    }

    ll sum(int l, int r) { return n ? fold(1, 0, n, l, r, 0, [&](ll a, int k) { return a + t[k].sum; }) : 0; }
    ll max_val(int l, int r) { return fold(1, 0, n, l, r, -LIM, [&](ll a, int k) { return max(a, t[k].mx); }); }
    ll min_val(int l, int r) { return fold(1, 0, n, l, r, LIM, [&](ll a, int k) { return min(a, t[k].mn); }); }
};
