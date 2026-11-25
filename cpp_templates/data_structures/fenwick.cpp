// Contents
//   Fenwick            Fenwick tree (0-indexed)
//   RangeFenwick       Fenwick tree with range update, point query (0-indexed)
//   Fenwick2D          2D Fenwick tree over points known in advance: point add, rectangle sum
//   rect_add_rect_sum  offline rectangle adds, then rectangle sums, mod a modulus (sweep with Fenwick trees), O((n + q) log n)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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

// Fenwick tree with range update, point query (0-indexed)
//   RangeFenwick(n)     n zeros, O(n)
//   add(l, r, v)        a[l..r) += v, O(log n)
//   get(i)              a[i], O(log n)
struct RangeFenwick {
    Fenwick f;

    RangeFenwick(int n = 0): f(n + 1) {}

    void add(int l, int r, ll v) {
        f.add(l, v);
        f.add(r, -v);
    }

    ll get(int i) const { return f.sum(i + 1); }
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

// offline: add w to every cell of each rectangle [l, r) x [d, u) in adds = {l, d, r, u, w}, then the sum over each
// rectangle in queries = {l, d, r, u}, mod mod; each add becomes 4 corner weights, and the sum over cells x < X, y < Y
// is the sum over corners (x, y, w) with x < X, y < Y of w (X - x)(Y - y) = w XY - w y X - w x Y + w x y,
// so a sweep over x with Fenwick trees over y for w, w y, w x and w x y answers it, O((n + q) log n)
vector<ll> rect_add_rect_sum(const vector<array<ll, 5>> &adds, const vector<array<ll, 4>> &queries, ll mod) {
    vector<array<ll, 3>> cs;  // {x, y, w}
    for (auto [l, d, r, u, w] : adds) {
        w %= mod;
        ll nw = (mod - w) % mod;
        cs.insert(cs.end(), {{l, d, w}, {l, u, nw}, {r, d, nw}, {r, u, w}});
    }
    sort(cs.begin(), cs.end());
    vector<ll> ys;
    for (auto &c : cs) ys.push_back(c[1]);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = ys.size();
    vector<array<ll, 4>> bit(m + 1);
    vector<array<ll, 4>> qs;  // {x, y, query id, sign}
    for (int i = 0; i < (int)queries.size(); i++) {
        auto [l, d, r, u] = queries[i];
        qs.insert(qs.end(), {{r, u, i, 1}, {l, u, i, -1}, {r, d, i, -1}, {l, d, i, 1}});
    }
    sort(qs.begin(), qs.end());
    vector<ll> ans(queries.size());
    size_t ci = 0;
    for (auto [X, Y, id, sign] : qs) {
        for (; ci < cs.size() && cs[ci][0] < X; ci++) {
            ll x = cs[ci][0] % mod, y = cs[ci][1] % mod, w = cs[ci][2];
            array<ll, 4> v{w, w * y % mod, w * x % mod, w * x % mod * y % mod};
            for (int i = lower_bound(ys.begin(), ys.end(), cs[ci][1]) - ys.begin() + 1; i <= m; i += i & -i) {
                for (int k = 0; k < 4; k++) bit[i][k] = (bit[i][k] + v[k]) % mod;
            }
        }
        array<ll, 4> s{};
        for (int i = lower_bound(ys.begin(), ys.end(), Y) - ys.begin(); i > 0; i -= i & -i) {  // corners with y < Y
            for (int k = 0; k < 4; k++) s[k] = (s[k] + bit[i][k]) % mod;
        }
        ll xm = X % mod, ym = Y % mod;
        ll f = (xm * ym % mod * s[0] - xm * s[1] % mod - ym * s[2] % mod + s[3]) % mod;
        ans[id] = ((ans[id] + sign * f) % mod + mod) % mod;
    }
    return ans;
}
