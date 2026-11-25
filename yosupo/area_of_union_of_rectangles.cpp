// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998244353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

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

// copy of MinCount and AddMinCount from monoids.cpp, for rect_union_area below; left out of the notebook
// {min, number of times it occurs}; leaves {a[i], 1}
struct MinCount {
    using T = pll;
    static T id() { return {LLONG_MAX, 0}; }
    static T op(const T &a, const T &b) {
        if (a.first != b.first) return a.first < b.first ? a : b;
        return {a.first, a.second + b.second};
    }
};

// range add, range {min, count}; leaves {a[i], 1}. number of zeros in a range of nonnegative
// values: len - (min == 0 ? count : 0), as in the sweep for the area of a union of rectangles
struct AddMinCount: MinCount {
    using F = ll;
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return {x.first == LLONG_MAX ? x.first : x.first + f, x.second}; }
    static F compose(const F &f, const F &g) { return f + g; }
};

// area of the union of axis-parallel rectangles {l, d, r, u} = [l, r) x [d, u), using LazySegTree and AddMinCount
// above: sweep over x with one leaf {cover count, height} per gap between consecutive y's, so the uncovered height
// is the count of the min when it is 0; the area must fit in ll, O(n log n)
ll rect_union_area(const vector<array<ll, 4>> &rects) {
    vector<array<ll, 4>> events;  // {x, d, u, +1 / -1}
    vector<ll> ys;
    for (auto [l, d, r, u] : rects) {
        events.push_back({l, d, u, 1});
        events.push_back({r, d, u, -1});
        ys.push_back(d);
        ys.push_back(u);
    }
    if (ys.empty()) return 0;
    sort(events.begin(), events.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = ys.size() - 1;
    vector<pll> leaves(m);
    for (int i = 0; i < m; i++) leaves[i] = {0, ys[i + 1] - ys[i]};
    LazySegTree<AddMinCount> seg(leaves);
    ll total = ys.back() - ys[0], area = 0;
    for (int i = 0; i < (int)events.size(); i++) {
        auto [x, d, u, w] = events[i];
        if (i) {
            pll mc = seg.query(0, m);
            area += (x - events[i - 1][0]) * (total - (mc.first == 0 ? mc.second : 0));
        }
        int lo = lower_bound(ys.begin(), ys.end(), d) - ys.begin(), hi = lower_bound(ys.begin(), ys.end(), u) - ys.begin();
        seg.update(lo, hi, w);
    }
    return area;
}

void solve() {
    ll n;
    cin >> n;
    vector<array<ll, 4>> rects(n);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < 4; j++) cin >> rects[i][j];
    }
    cout << rect_union_area(rects) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
