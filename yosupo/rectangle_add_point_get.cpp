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

// Fenwick tree (0-indexed)
//   Fenwick(n)          n zeros, O(n)
//   Fenwick(a)           build from a, O(n)
//   add(i, v)            a[i] += v, O(log n)
//   sum(r)               sum of a[0..r), O(log n)
//   sum(l, r)            sum of a[l..r), O(log n)
//   get(i)               a[i], O(log n)
//   set(i, v)            a[i] = v, O(log n)
//   lower_bound(s)       smallest p with sum(p + 1) >= s, n if none; requires a[i] >= 0, O(log n)
struct Fenwick {
    int n;
    vector<ll> t;

    Fenwick(int n = 0): n(n), t(n + 1, 0) {}

    Fenwick(const vector<ll> &a): Fenwick((int)a.size()) {
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }

    void add(int i, ll v) {
        for (i++; i <= n; i += i & -i) t[i] += v;
    }

    ll sum(int r) const {
        ll res = 0;
        for (; r > 0; r -= r & -r) res += t[r];
        return res;
    }

    ll sum(int l, int r) const { return sum(r) - sum(l); }

    ll get(int i) const { return sum(i, i + 1); }

    void set(int i, ll v) { add(i, v - get(i)); }

    int lower_bound(ll s) const {
        int p = 0;
        for (int k = n ? __lg(n) : 0; k >= 0 && n; k--) {
            if (p + (1 << k) <= n && t[p + (1 << k)] < s) {
                p += 1 << k;
                s -= t[p];
            }
        }
        return p;
    }
};

// 2D Fenwick tree over a set of points known in advance (offline): add weight to a point, sum over a rectangle
// each node of a Fenwick tree over x keeps the sorted y's it covers and a Fenwick tree (above) over them
//   Fenwick2D(pts)            pts = {x, y} of every point that will ever get weight (repeats are fine), O(n log n)
//   add(x, y, w)              add w at (x, y), which must be in pts, O(log^2 n)
//   sum(xl, yl, xr, yr)       sum of the weights at xl <= x < xr and yl <= y < yr, O(log^2 n)
struct Fenwick2D {
    vector<ll> xs;
    vector<vector<ll>> ys;
    vector<Fenwick> fen;

    Fenwick2D(const vector<pll> &pts) {
        for (auto [x, y] : pts) xs.push_back(x);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int n = xs.size();
        ys.resize(n + 1);
        for (auto [x, y] : pts)
            for (int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1; i <= n; i += i & -i) ys[i].push_back(y);
        for (int i = 1; i <= n; i++) {
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
            fen.emplace_back(ys[i].size());
        }
    }

    static int pos(const vector<ll> &v, ll y) { return lower_bound(v.begin(), v.end(), y) - v.begin(); }

    void add(ll x, ll y, ll w) {
        for (int i = pos(xs, x) + 1; i <= (int)xs.size(); i += i & -i) fen[i - 1].add(pos(ys[i], y), w);
    }

    ll prefix(ll xr, ll yl, ll yr) const {  // x < xr, yl <= y < yr
        ll res = 0;
        for (int i = pos(xs, xr); i > 0; i -= i & -i) res += fen[i - 1].sum(pos(ys[i], yl), pos(ys[i], yr));
        return res;
    }

    ll sum(ll xl, ll yl, ll xr, ll yr) const { return prefix(xr, yl, yr) - prefix(xl, yl, yr); }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<array<ll, 6>> ops;  // {type, l, d, r, u, w} or {1, x, y}
    for (ll i = 0; i < n; i++) {
        ll l, d, r, u, w;
        cin >> l >> d >> r >> u >> w;
        ops.push_back({0, l, d, r, u, w});
    }
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll l, d, r, u, w;
            cin >> l >> d >> r >> u >> w;
            ops.push_back({0, l, d, r, u, w});
        }
        else {
            ll x, y;
            cin >> x >> y;
            ops.push_back({1, x, y, 0, 0, 0});
        }
    }
    vector<pll> pts;
    for (auto &o : ops) if (o[0] == 0) pts.insert(pts.end(), {{o[1], o[2]}, {o[3], o[2]}, {o[1], o[4]}, {o[3], o[4]}});
    Fenwick2D fen(pts);
    for (auto &o : ops) {
        if (o[0] == 0) {
            fen.add(o[1], o[2], o[5]);
            fen.add(o[3], o[2], -o[5]);
            fen.add(o[1], o[4], -o[5]);
            fen.add(o[3], o[4], o[5]);
        }
        else {
            cout << fen.sum(0, 0, o[1] + 1, o[2] + 1) << "\n";
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
