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

// 2D point / vector
//   +, -, * scalar, / scalar   vector arithmetic, O(1)
//   ==, <                      exact comparisons (< is by x, then y), O(1)
struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0): x(x), y(y) {}
};

void solve() {
    ll n;
    cin >> n;
    vector<Point> p(n);
    for (ll i = 0; i < n; i++) {
        ll xi, yi;
        cin >> xi >> yi;
        p[i] = {xi, yi};
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ans += (p[i].y + p[(i + 1) % n].y) * (p[i].x - p[(i + 1) % n].x);
    }
    cout << abs(ans) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
