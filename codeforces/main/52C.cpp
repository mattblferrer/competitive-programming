// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// lazy segment tree (iterative), range update and query on [l, r)
// example: range add, range sum; T = {sum, length}, F = amount added
// build from leaves {x, 1}, since the default leaves {0, 0} have length 0
struct Spec {
    using T = ll;
    using F = ll;
    static T id() { return LLONG_MAX; }
    static T op(const T &a, const T &b) { return min(a, b); }
    static F fid() { return 0; }
    static T apply(const F &f, const T &x) { return x + f; }
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

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    LazySegTree<Spec> tree(a);

    ll m;
    cin >> m;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    stringstream ss;
    for (ll i = 0; i < m; i++) {
        string line;
        getline(cin, line);
        ss << line;
        ll lf = -1, rg = -1, v = 0;
        ss >> lf >> rg;

        if (!(ss >> v)) {  // rmq operation
            if (lf > rg) {
                cout << min(tree.query(lf, n), tree.query(0, rg + 1)) << "\n";
            }
            else {
                cout << tree.query(lf, rg + 1) << "\n";
            }
        }
        else {  // inc operation
            if (lf > rg) {
                tree.update(lf, n, v);
                tree.update(0, rg + 1, v);
            }
            else {
                tree.update(lf, rg + 1, v);
            }
        }
        ss.clear();
        ss.flush();
    }
}

int main() {
    ios_base::sync_with_stdio(false);   
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
