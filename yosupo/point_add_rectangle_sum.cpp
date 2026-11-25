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
    vector<array<ll, 3>> init(n);
    vector<pll> pts;
    for (ll i = 0; i < n; i++) {
        cin >> init[i][0] >> init[i][1] >> init[i][2];
        pts.push_back({init[i][0], init[i][1]});
    }
    vector<array<ll, 5>> qs(q);
    for (ll i = 0; i < q; i++) {
        cin >> qs[i][0];
        if (qs[i][0] == 0) {
            cin >> qs[i][1] >> qs[i][2] >> qs[i][3];
            pts.push_back({qs[i][1], qs[i][2]});
        }
        else {
            cin >> qs[i][1] >> qs[i][2] >> qs[i][3] >> qs[i][4];
        }
    }
    Fenwick2D fen(pts);
    for (ll i = 0; i < n; i++) fen.add(init[i][0], init[i][1], init[i][2]);
    for (ll i = 0; i < q; i++) {
        if (qs[i][0] == 0) fen.add(qs[i][1], qs[i][2], qs[i][3]);
        else cout << fen.sum(qs[i][1], qs[i][2], qs[i][3], qs[i][4]) << "\n";
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
