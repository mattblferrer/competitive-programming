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

// divide and conquer DP optimization: computes cur[j] = min over k <= j of prev[k] + cost(k, j) for j in [l, r], O(n log n) cost calls
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

// Knuth optimization, O(n^2): dp[i][j] = min over i <= k < j of dp[i][k] + dp[k + 1][j] + cost(i, j), dp[i][i] = base(i)
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
