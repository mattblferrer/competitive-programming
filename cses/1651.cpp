#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

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

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n + 1);
    for (ll i = 1; i <= n; i++) cin >> x[i];
    LazySegTree<Spec> tree(n + 1);
    for (ll i = 1; i <= n; i++) tree.set(i, {x[i], 1});
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll a, b, u;
            cin >> a >> b >> u;
            tree.update(a, b + 1, u);
        }
        else if (type == 2) {
            ll k;
            cin >> k;
            cout << tree.get(k).first << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}