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

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    SegTreeBeats tree(a);

    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;

        if (type == 0) {
            ll l, r, b;
            cin >> l >> r >> b;
            tree.chmin(l, r, b);
        }
        else if (type == 1) {
            ll l, r, b;
            cin >> l >> r >> b;
            tree.chmax(l, r, b);
        }
        else if (type == 2) {
            ll l, r, b;
            cin >> l >> r >> b;
            tree.add(l, r, b);
        }
        else if (type == 3) {
            ll l, r;
            cin >> l >> r;
            cout << tree.sum(l, r) << "\n";
        }
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
