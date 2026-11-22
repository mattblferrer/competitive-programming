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

void solve() {
    ll n, q;
    cin >> n >> q;
    LineContainer<false> lc;
    for (ll i = 0; i < n; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        lc.add(ai, bi);
    }
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 0) {
            ll ai, bi;
            cin >> ai >> bi;
            lc.add(ai, bi);
        }
        else if (type == 1) {
            ll p;
            cin >> p;
            cout << lc.query(p) << "\n";
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
