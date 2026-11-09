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

const ll EPS = 0;

// 2D point / vector
//   +, -, * scalar, / scalar   vector arithmetic, O(1)
//   ==, <                      exact comparisons (< is by x, then y), O(1)
struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0): x(x), y(y) {}
    Point operator+(const Point &o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point &o) const { return {x - o.x, y - o.y}; }
    Point operator*(ll k) const { return {x * k, y * k}; }
    Point operator/(ll k) const { return {x / k, y / k}; }
    bool operator==(const Point &o) const { return x == o.x && y == o.y; }
    bool operator<(const Point &o) const { return x != o.x ? x < o.x : y < o.y; }
};

// cross product, O(1)
ll cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

// cross product of b - a and c - a; positive if a, b, c turn counter-clockwise, O(1)
ll cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

// convex hull in counter-clockwise order (monotone chain), O(n log n)
// strict by default; with keep_collinear, also keeps input points in the middle of hull edges
// (if all points are collinear, returns them sorted)
vector<Point> convex_hull(vector<Point> p, bool keep_collinear = false) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    ll lim = keep_collinear ? -EPS : EPS;
    vector<Point> h(2 * n);
    for (int i = 0; i < n; h[k++] = p[i++])
        while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) < lim) k--;
    for (int i = n - 2, t = k + 1; i >= 0; h[k++] = p[i--])
        while (k >= t && cross(h[k - 2], h[k - 1], p[i]) < lim) k--;
    if (k == 2 * n - 1) return p;  // nothing popped: all points are collinear
    h.resize(k - 1);
    return h;
}

void solve() {
    ll n;
    cin >> n;
    vector<Point> p(n);
    for (ll i = 0; i < n; i++) {
        ll xi, yi;
        cin >> xi >> yi;
        p[i] = {xi, yi};
    }
    vector<Point> ch = convex_hull(p, true);
    ll k = ch.size();
    cout << k << "\n";
    for (ll i = 0; i < k; i++) {
        cout << ch[i].x << " " << ch[i].y << "\n";
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
