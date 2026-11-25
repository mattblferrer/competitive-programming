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

// best approximations of x/y (x, y >= 1) by fractions with numerator and denominator in [1, n]: returns {p, q, r, s},
// p/q the largest <= x/y (0/1 if none) and r/s the smallest >= x/y (1/0 if none); walks down the Stern-Brocot tree
// toward x/y one run at a time, each run as long as it stays on its side of x/y and within n, O(log)
array<ll, 4> rational_approx(ll n, ll x, ll y) {
    ll g = gcd(x, y), a = 0, b = 1, c = 1, d = 0;  // invariant a/b <= x/y <= c/d
    x /= g, y /= g;
    while (true) {
        if (a * y == x * b) return {a, b, a, b};
        if (c * y == x * d) return {c, d, c, d};
        ll k = (x * b - a * y) / (c * y - d * x);  // right run: a/b moves toward x/y
        k = min(k, (n - a) / c);
        if (d) k = min(k, (n - b) / d);
        a += k * c, b += k * d;
        if (a * y == x * b) return {a, b, a, b};
        ll k2 = (c * y - d * x) / (x * b - a * y);  // left run: c/d moves toward x/y
        if (a) k2 = min(k2, (n - c) / a);
        k2 = min(k2, (n - d) / b);
        c += k2 * a, d += k2 * b;
        if (!k && !k2) return {a, b, c, d};
    }
}

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;
    array<ll, 4> r = rational_approx(n, x, y);
    cout << r[0] << " " << r[1] << " " << r[2] << " " << r[3] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
