#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;


// Iterative, point-update [a, b)
struct Monoid {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
};

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

// Recursive, range-update [a, b)
struct Spec {
    using T = pll;
    using F = ll;
    static T id() { return {0, 0}; }
    static T op(const T &a, const T &b) { return {a.first + b.first, a.second + b.second}; }
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return {x.first + f * x.second, x.second}; }
    static F compose(const F &f, const F &g) { return f + g; }
};

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

// Iterative, 2D point-update [a, b]
struct Monoid {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
};

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