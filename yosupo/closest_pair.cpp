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
const ld EPS = 1e-9;

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// 2D point / vector
//   +, -, * scalar, / scalar   vector arithmetic, O(1)
//   ==, <                      exact comparisons (< is by x, then y), O(1)
struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0): x(x), y(y) {}
    Point operator+(const Point &o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point &o) const { return {x - o.x, y - o.y}; }
    Point operator*(ld k) const { return {x * k, y * k}; }
    Point operator/(ld k) const { return {x / k, y / k}; }
    bool operator==(const Point &o) const { return x == o.x && y == o.y; }
    bool operator<(const Point &o) const { return x != o.x ? x < o.x : y < o.y; }
};

// dot product, O(1)
ld dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

// squared length, O(1)
ld norm(Point a) { return dot(a, a); }

// two of the points at the smallest distance (line sweep), n >= 2, O(n log n)
// compares squared distances, so exact for integer coordinates up to ~1e9
pair<Point, Point> closest_pair(vector<Point> p) {
    sort(p.begin(), p.end(), [](const Point &a, const Point &b) { return a.y < b.y; });
    set<Point> box;
    pair<Point, Point> res = {p[0], p[1]};
    ld best = HUGE_VALL;  // squared
    for (int l = 0, i = 0; i < (int)p.size(); i++) {
        ld d = sqrtl(best);
        while (p[i].y - p[l].y > d) box.erase(p[l++]);
        for (auto it = box.lower_bound(Point(p[i].x - d, -HUGE_VALL)); it != box.end() && it->x <= p[i].x + d; it++)
            if (norm(p[i] - *it) < best) best = norm(p[i] - *it), res = {*it, p[i]};
        box.insert(p[i]);
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;
    vector<Point> p(n);
    map<pll, vector<ll>> idx;
    for (ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        p[i] = Point(x, y);
        idx[{x, y}].push_back(i);
    }
    auto [a, b] = closest_pair(p);
    vector<ll> &ia = idx[{(ll)a.x, (ll)a.y}], &ib = idx[{(ll)b.x, (ll)b.y}];
    ll i = ia[0], j = ib[0] != i ? ib[0] : ib[1];
    cout << i << " " << j << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
