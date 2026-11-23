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

// squared length, O(1)
ld norm(Point a) { return dot(a, a); }

// sorts p by polar angle around o, counter-clockwise from direction s: angles in [0, 2 pi), or (0, 2 pi] if s_last
// (points in direction s go last); points equal to o count as direction (1, 0), like atan2(0, 0) = 0; ties nearest first
// default: from angle 0 up to 2 pi, points equal to o first; atan2 order (-pi, pi]: sort_by_angle(p, o, {-1, 0}, true)
// exact for integer coordinates up to ~1e9, O(n log n)
void sort_by_angle(vector<Point> &p, Point o = Point(), Point s = Point(1, 0), bool s_last = false) {
    auto dir = [&](const Point &a) { return a == o ? Point(1, 0) : a - o; };
    auto half = [&](const Point &u) {  // 0: angle from s in [0, pi) ((0, pi] if s_last), 1: the rest
        ld c = cross(s, u), d = dot(s, u);
        return c > 0 || (c == 0 && (s_last ? d < 0 : d > 0)) ? 0 : 1;
        };
    sort(p.begin(), p.end(), [&](const Point &a, const Point &b) {
        Point u = dir(a), v = dir(b);
        if (half(u) != half(v)) return half(u) < half(v);
        ld c = cross(u, v);
        return c != 0 ? c > 0 : norm(a - o) < norm(b - o);
        });
}

void solve() {
    ll n;
    cin >> n;
    vector<Point> p(n);
    for (ll i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    sort_by_angle(p, Point(), Point(-1, 0), true);
    for (ll i = 0; i < n; i++) cout << (ll)p[i].x << " " << (ll)p[i].y << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
