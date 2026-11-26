// Contents
//   LineContainer               dynamic convex hull trick: add lines in any order, query at any x
//   LiChao                      Li Chao tree on integer x in [lo, hi]
//   PersistentLiChao            persistent Li Chao tree for minimum queries on integer x in [lo, hi]
//   dnc_opt                     divide and conquer DP optimization
//   knuth_opt                   Knuth optimization, O(n^2)
//   min_plus_convex_convex      c[k] = min of a[i] + b[j] over i + j = k for convex a and b (merge of slopes), O(n + m)
//   min_plus_convex_arbitrary   c[k] = min of a[i] + b[j] over i + j = k for convex a and any b (monotone minima),
//                               O((n + m) log(n + m))
//   min_plus_concave_arbitrary  c[k] = min of a[i] + b[j] over i + j = k for concave a and any b,
//                               O((n + m) log^2 (n + m))
//   SlopeTrick                  convex piecewise linear function: add |x - a| and ramps, prefix / suffix min,
//                               shift, merge
//   aliens                      Aliens trick (WQS binary search): min cost with exactly k items for a cost convex in k

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// dynamic convex hull trick: add lines in any order, query at any x
// MAX = true keeps the upper envelope, false keeps the lower envelope; all values must fit in ll
//   add(m, b)   add the line y = m * x + b, O(log n) amortized
//   query(x)    best value at x; requires at least one line, O(log n)
template <bool MAX = true>
struct LineContainer {
    struct Line {
        mutable ll m, b, p;  // p = last x where this line is optimal
        bool operator<(const Line &o) const { return m < o.m; }
        bool operator<(ll x) const { return p < x; }
    };
    multiset<Line, less<>> hull;
    static constexpr ll LIMIT = LLONG_MAX;

    static ll floor_div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }

    // sets x->p and returns true if the line after x makes the line y useless
    bool intersect(typename multiset<Line, less<>>::iterator x, typename multiset<Line, less<>>::iterator y) {
        if (y == hull.end()) {
            x->p = LIMIT;
            return false;
        }
        if (x->m == y->m) x->p = x->b > y->b ? LIMIT : -LIMIT;
        else x->p = floor_div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }

    void add(ll m, ll b) {
        if (!MAX) m = -m, b = -b;
        auto z = hull.insert({m, b, 0}), y = z++, x = y;
        while (intersect(y, z)) z = hull.erase(z);
        if (x != hull.begin() && intersect(--x, y)) intersect(x, y = hull.erase(y));
        while ((y = x) != hull.begin() && (--x)->p >= y->p) intersect(x, hull.erase(y));
    }

    ll query(ll x) const {
        auto l = hull.lower_bound(x);
        ll y = l->m * x + l->b;
        return MAX ? y : -y;
    }
};

// Li Chao tree on integer x in [lo, hi], nodes are created as needed so the range can be large
// MAX = false keeps minimums, true keeps maximums; all line values on [lo, hi] must fit in ll and stay below INF
//   LiChao(lo, hi)            empty tree on [lo, hi], O(1)
//   insert(v, line, a, b)     insert a line into node v covering [a, b], O(log(hi - lo))
//   add(m, b)                 add y = m * x + b for all x, O(log(hi - lo))
//   add_segment(l, r, m, b)   add y = m * x + b only for x in [l, r], O(log^2(hi - lo))
//   query(x)                  best value at x, INF (-INF if MAX) if no line covers x, O(log(hi - lo))
template <bool MAX = false>
struct LiChao {
    struct Line {
        ll m, b;
        ll eval(ll x) const { return m * x + b; }
    };
    struct Node { Line line; int l, r; };
    ll lo, hi;
    vector<Node> t;  // t[0] is the root; a child index of 0 means no child

    LiChao(ll lo, ll hi): lo(lo), hi(hi), t(1, Node{Line{0, INF}, 0, 0}) {}

    int new_node(Line line) {
        t.push_back({line, 0, 0});
        return t.size() - 1;
    }

    void insert(int v, Line nw, ll a, ll b) {
        while (true) {
            ll m = a + (b - a) / 2;
            bool left = nw.eval(a) < t[v].line.eval(a);
            bool mid = nw.eval(m) < t[v].line.eval(m);
            if (mid) swap(t[v].line, nw);
            if (a == b) return;
            if (left != mid) {
                if (!t[v].l) {
                    int id = new_node(nw);
                    t[v].l = id;
                    return;
                }
                v = t[v].l;
                b = m;
            } else {
                if (!t[v].r) {
                    int id = new_node(nw);
                    t[v].r = id;
                    return;
                }
                v = t[v].r;
                a = m + 1;
            }
        }
    }

    void add(ll m, ll b) { insert(0, MAX ? Line{-m, -b} : Line{m, b}, lo, hi); }

    void add_segment(ll l, ll r, ll m, ll b) { segment(0, MAX ? Line{-m, -b} : Line{m, b}, lo, hi, l, r); }

    void segment(int v, Line nw, ll a, ll b, ll l, ll r) {
        if (r < a || b < l) return;
        if (l <= a && b <= r) {
            insert(v, nw, a, b);
            return;
        }
        ll m = a + (b - a) / 2;
        if (!t[v].l) {
            int id = new_node(Line{0, INF});
            t[v].l = id;
        }
        if (!t[v].r) {
            int id = new_node(Line{0, INF});
            t[v].r = id;
        }
        segment(t[v].l, nw, a, m, l, r);
        segment(t[v].r, nw, m + 1, b, l, r);
    }

    ll query(ll x) const {
        ll res = INF, a = lo, b = hi;
        int v = 0;
        while (true) {
            res = min(res, t[v].line.eval(x));
            if (a == b) break;
            ll m = a + (b - a) / 2;
            int next = x <= m ? t[v].l : t[v].r;
            if (x <= m) b = m;
            else a = m + 1;
            if (!next) break;
            v = next;
        }
        return MAX ? -res : res;
    }
};

// persistent Li Chao tree for minimum queries on integer x in [lo, hi]; version 0 has no lines
// all line values on [lo, hi] must fit in ll
//   PersistentLiChao(lo, hi)   empty tree on [lo, hi], O(1)
//   add(ver, m, b)             add y = m * x + b to a copy of ver, returns the new version, O(log(hi - lo))
//   query(ver, x)              minimum over the lines of ver at x, INF if there are none, O(log(hi - lo))
struct PersistentLiChao {
    struct Line {
        ll m, b;
        ll eval(ll x) const { return m * x + b; }
    };
    struct Node { Line line; int l, r; };
    ll lo, hi;
    vector<Node> t;  // t[0] is the empty node
    vector<int> roots;

    PersistentLiChao(ll lo, ll hi): lo(lo), hi(hi), t(1, Node{Line{0, INF}, 0, 0}), roots(1, 0) {}

    int insert(int prev, Line nw, ll a, ll b) {
        t.push_back(t[prev]);
        int id = t.size() - 1;
        ll m = a + (b - a) / 2;  // rounds down for negative a too, so the recursion always shrinks
        bool left = nw.eval(a) < t[id].line.eval(a);
        bool mid = nw.eval(m) < t[id].line.eval(m);
        if (mid) swap(t[id].line, nw);
        if (a == b) return id;
        if (left != mid) {
            int child = insert(t[prev].l, nw, a, m);
            t[id].l = child;
        } else {
            int child = insert(t[prev].r, nw, m + 1, b);
            t[id].r = child;
        }
        return id;
    }

    int add(int ver, ll m, ll b) {
        roots.push_back(insert(roots[ver], Line{m, b}, lo, hi));
        return roots.size() - 1;
    }

    ll query(int ver, ll x) const {
        ll res = INF, a = lo, b = hi;
        for (int cur = roots[ver]; cur; ) {
            res = min(res, t[cur].line.eval(x));
            if (a == b) break;
            ll m = a + (b - a) / 2;
            if (x <= m) cur = t[cur].l, b = m;
            else cur = t[cur].r, a = m + 1;
        }
        return res;
    }
};

// divide and conquer DP optimization: computes cur[j] = min over k <= j of prev[k] + cost(k, j) for j in [l, r],
// O(n log n) cost calls
// requires the optimal k to be non-decreasing in j (e.g. cost satisfies the quadrangle inequality)
// call with k_lo = 0, k_hi = n - 1, l = 0, r = n - 1
template <class Cost>
void dnc_opt(const vector<ll> &prev, vector<ll> &cur, Cost cost, int k_lo, int k_hi, int l, int r) {
    if (l > r) return;
    int mid = (l + r) / 2, best = k_lo;
    cur[mid] = INF;
    for (int k = k_lo; k <= min(mid, k_hi); k++) {
        if (prev[k] < INF && prev[k] + cost(k, mid) < cur[mid]) {
            cur[mid] = prev[k] + cost(k, mid);
            best = k;
        }
    }
    dnc_opt(prev, cur, cost, k_lo, best, l, mid - 1);
    dnc_opt(prev, cur, cost, best, k_hi, mid + 1, r);
}

// Knuth optimization, O(n^2): dp[i][j] = min over i <= k < j of dp[i][k] + dp[k + 1][j] + cost(i, j),
// dp[i][i] = base(i)
// requires opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]; returns the full dp table, the answer is usually dp[0][n - 1]
template <class Cost, class Base>
vector<vector<ll>> knuth_opt(int n, Cost cost, Base base) {
    vector<vector<ll>> dp(n, vector<ll>(n, INF));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = base(i);
        opt[i][i] = i;
        for (int j = i + 1; j < n; j++) {
            ll c = cost(i, j);
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                ll cur = dp[i][k] + dp[k + 1][j] + c;
                if (cur < dp[i][j]) {
                    dp[i][j] = cur;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp;
}

// c[k] = min over i + j = k of a[i] + b[j] for convex a and b (a[i + 1] - a[i] nondecreasing): c starts at
// a[0] + b[0] and its differences are those of a and b merged in sorted order, O(n + m)
vector<ll> min_plus_convex_convex(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    vector<ll> c(n + m - 1);
    c[0] = a[0] + b[0];
    for (int i = 0, j = 0, k = 1; k < n + m - 1; k++) {
        if (j == m - 1 || (i < n - 1 && a[i + 1] - a[i] < b[j + 1] - b[j])) c[k] = c[k - 1] + a[i + 1] - a[i], i++;
        else c[k] = c[k - 1] + b[j + 1] - b[j], j++;
    }
    return c;
}

// c[k] = min over i + j = k of a[i] + b[j] for convex a and any b: the matrix b[j] + a[k - j] is Monge, so the
// best j is nondecreasing in k and divide and conquer over k (monotone minima) finds it, O((n + m) log(n + m))
vector<ll> min_plus_convex_arbitrary(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    vector<ll> c(n + m - 1);
    auto rec = [&](auto &self, int klo, int khi, int jlo, int jhi) -> void {  // rows [klo, khi), best j in [jlo, jhi]
        if (klo >= khi) return;
        int k = (klo + khi) / 2, best = -1;
        for (int j = max(jlo, k - n + 1); j <= min({jhi, k, m - 1}); j++) {
            if (best == -1 || b[j] + a[k - j] < c[k]) c[k] = b[j] + a[k - j], best = j;
        }
        self(self, klo, k, jlo, best);
        self(self, k + 1, khi, best, jhi);
    };
    rec(rec, 0, n + m - 1, 0, m - 1);
    return c;
}

// c[k] = min over i + j = k of a[i] + b[j] for concave a (a[i + 1] - a[i] nonincreasing) and any b: on the cells
// (k, j) with 0 <= k - j < n the best j is nonincreasing in k, but the band of cells shifts right as k grows, so it
// is cut into full rectangles (halving the longer side) and each gets monotone minima, O((n + m) log^2 (n + m))
vector<ll> min_plus_concave_arbitrary(const vector<ll> &a, const vector<ll> &b) {
    int n = a.size(), m = b.size();
    vector<ll> c(n + m - 1, INF);
    auto mono = [&](auto &self, int klo, int khi, int jlo, int jhi) -> void {  // rows [klo, khi), best j in [jlo, jhi)
        if (klo >= khi) return;
        int k = (klo + khi) / 2, best = jlo;
        ll val = a[k - jlo] + b[jlo];
        for (int j = jlo + 1; j < jhi; j++) {
            if (a[k - j] + b[j] < val) val = a[k - j] + b[j], best = j;
        }
        c[k] = min(c[k], val);
        self(self, klo, k, best, jhi);
        self(self, k + 1, khi, jlo, best + 1);
    };
    auto rec = [&](auto &self, int klo, int khi, int jlo, int jhi) -> void {  // rows [klo, khi), columns [jlo, jhi)
        int lo = klo - (jhi - 1), hi = khi - 1 - jlo;  // range of k - j
        if (hi < 0 || lo >= n) return;
        if (lo >= 0 && hi < n) return mono(mono, klo, khi, jlo, jhi);
        if (khi - klo >= jhi - jlo) {
            int mid = (klo + khi) / 2;
            self(self, klo, mid, jlo, jhi);
            self(self, mid, khi, jlo, jhi);
        } else {
            int mid = (jlo + jhi) / 2;
            self(self, klo, khi, jlo, mid);
            self(self, klo, khi, mid, jhi);
        }
    };
    rec(rec, 0, n + m - 1, 0, m);
    return c;
}

// slope trick: a convex piecewise linear f(x) with integer breakpoints, as its minimum and two heaps of breakpoints
// (L: where the slope goes up by 1 left of the minimum, R: right of it), each with a lazy shift
//   min()                  min of f, O(1)
//   argmin()               {lo, hi}: f is minimal exactly on [lo, hi] (+-INF when unbounded), O(1)
//   add_const(a)           f += a, O(1)
//   add_x_minus_a(a)       f += max(0, x - a), O(log n)
//   add_a_minus_x(a)       f += max(0, a - x), O(log n)
//   add_abs(a)             f += |x - a|, O(log n)
//   prefix_min()           f(x) = min over y <= x of f(y) (drops R), O(1) amortized
//   suffix_min()           f(x) = min over y >= x of f(y) (drops L), O(1) amortized
//   shift(a, b)            f(x) = min over x - b <= y <= x - a of f(y), a <= b (shift(a, a) moves f right by a), O(1)
//   merge(o)               f += o (small to large; o is emptied), O(|o| log n)
//   eval(x)                f(x), O(n log n)
struct SlopeTrick {
    ll min_f = 0, add_l = 0, add_r = 0;
    priority_queue<ll> L;
    priority_queue<ll, vector<ll>, greater<>> R;

    ll top_l() const { return L.empty() ? -INF : L.top() + add_l; }
    ll top_r() const { return R.empty() ? INF : R.top() + add_r; }
    void push_l(ll a) { L.push(a - add_l); }
    void push_r(ll a) { R.push(a - add_r); }
    ll pop_l() { ll v = top_l(); L.pop(); return v; }
    ll pop_r() { ll v = top_r(); R.pop(); return v; }

    ll min() const { return min_f; }
    pll argmin() const { return {top_l(), top_r()}; }
    void add_const(ll a) { min_f += a; }

    void add_x_minus_a(ll a) {
        if (!L.empty()) min_f += max(0LL, top_l() - a);
        push_l(a);
        push_r(pop_l());
    }

    void add_a_minus_x(ll a) {
        if (!R.empty()) min_f += max(0LL, a - top_r());
        push_r(a);
        push_l(pop_r());
    }

    void add_abs(ll a) { add_x_minus_a(a), add_a_minus_x(a); }
    void prefix_min() { R = {}; }
    void suffix_min() { L = {}; }
    void shift(ll a, ll b) { add_l += a, add_r += b; }

    void merge(SlopeTrick &o) {
        if (L.size() + R.size() < o.L.size() + o.R.size()) swap(*this, o);
        min_f += o.min_f;
        while (!o.L.empty()) add_a_minus_x(o.pop_l());
        while (!o.R.empty()) add_x_minus_a(o.pop_r());
        o = SlopeTrick();
    }

    ll eval(ll x) const {
        ll res = min_f;
        for (auto l = L; !l.empty(); l.pop()) res += max(0LL, l.top() + add_l - x);
        for (auto r = R; !r.empty(); r.pop()) res += max(0LL, x - r.top() - add_r);
        return res;
    }
};

// Aliens trick (WQS binary search, Lagrangian relaxation): f(k) = min cost of a solution with exactly k items, for f
// convex in k with integer values. solve(lambda) must return {min over all solutions of cost + lambda * count, the
// smallest count achieving that min}; [lo, hi] must hold some lambda whose count is <= k, i.e. hi >= f(k) - f(k + 1)
// (lo = -hi with hi = max |f(j + 1) - f(j)| works). To maximize a concave f, return -cost and negate the answer.
// O(log(hi - lo)) calls to solve
template <class Solve>
ll aliens(ll k, ll lo, ll hi, Solve solve) {
    while (lo < hi) {  // smallest lambda with count(lambda) <= k
        ll mid = lo + (hi - lo) / 2;
        if (solve(mid).second <= k) hi = mid;
        else lo = mid + 1;
    }
    return solve(lo).first - lo * k;
}
