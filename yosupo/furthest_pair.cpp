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

// cross product, O(1)
ld cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

// cross product of b - a and c - a; positive if a, b, c turn counter-clockwise, O(1)
ld cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

// squared length, O(1)
ld norm(Point a) { return dot(a, a); }

// convex hull in counter-clockwise order (monotone chain), O(n log n)
// strict by default; with keep_collinear, also keeps input points in the middle of hull edges
// (if all points are collinear, returns them sorted)
vector<Point> convex_hull(vector<Point> p, bool keep_collinear = false) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    ld lim = keep_collinear ? -EPS : EPS;
    vector<Point> h(2 * n);
    for (int i = 0; i < n; h[k++] = p[i++])
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) < lim) k--;
    for (int i = n - 2, t = k + 1; i >= 0; h[k++] = p[i--])
        while (k >= t && cross(h[k - 2], h[k - 1], p[i]) < lim) k--;
    if (k == 2 * n - 1) return p;  // nothing popped: all points are collinear
    h.resize(k - 1);
    return h;
}

// two of the points at the largest distance (diameter, rotating calipers), n >= 1, O(n log n)
// compares squared distances, so exact for integer coordinates up to ~1e9
pair<Point, Point> furthest_pair(const vector<Point> &pts) {
    vector<Point> h = convex_hull(pts);
    int k = h.size();
    if (k < 3 || fabsl(cross(h[0], h[1], h[2])) < EPS) return {h[0], h.back()};  // collinear: hull is sorted
    pair<Point, Point> res = {h[0], h[1]};
    for (int i = 0, j = 1; i < k; i++) {
        int ni = (i + 1) % k;
        while (cross(h[i], h[ni], h[(j + 1) % k]) > cross(h[i], h[ni], h[j])) j = (j + 1) % k;
        for (Point q : {h[i], h[ni]}) if (norm(q - h[j]) > norm(res.first - res.second)) res = {q, h[j]};
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
    auto [a, b] = furthest_pair(p);
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
