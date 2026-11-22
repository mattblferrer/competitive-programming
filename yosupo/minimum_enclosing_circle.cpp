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

// length, O(1)
ld abs(Point a) { return hypotl(a.x, a.y); }

// distance between a and b, O(1)
ld dist(Point a, Point b) { return abs(a - b); }

// point with barycentric weights a, b, c in triangle ABC, O(1)
Point bary(Point A, Point B, Point C, ld a, ld b, ld c) { return (A * a + B * b + C * c) / (a + b + c); }

// circumcenter of a non-degenerate triangle, O(1)
Point circumcenter(Point A, Point B, Point C) {
    ld a = norm(B - C), b = norm(C - A), c = norm(A - B);
    return bary(A, B, C, a * (b + c - a), b * (c + a - b), c * (a + b - c));
}

// smallest circle containing all points, returned as {center, radius}, O(n) expected
pair<Point, ld> min_enclosing_circle(vector<Point> p) {
    shuffle(p.begin(), p.end(), mt19937(chrono::steady_clock::now().time_since_epoch().count()));
    Point c;
    ld r = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (dist(c, p[i]) <= r + EPS) continue;
        c = p[i];
        r = 0;
        for (int j = 0; j < i; j++) {
            if (dist(c, p[j]) <= r + EPS) continue;
            c = (p[i] + p[j]) / 2;
            r = dist(c, p[i]);
            for (int k = 0; k < j; k++) {
                if (dist(c, p[k]) <= r + EPS) continue;
                c = circumcenter(p[i], p[j], p[k]);
                r = dist(c, p[i]);
            }
        }
    }
    return {c, r};
}

void solve() {
    ll n;
    cin >> n;
    vector<Point> pts(n);
    for (ll i = 0; i < n; i++) {
        ld xi, yi;
        cin >> xi >> yi;
        pts[i] = {xi, yi};
    }
    pair<Point, ld> mec = min_enclosing_circle(pts);
    for (ll i = 0; i < n; i++) {
        if (abs(dist(mec.first, pts[i]) - mec.second) <= EPS) cout << 1 << "";
        else cout << 0 << "";
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
