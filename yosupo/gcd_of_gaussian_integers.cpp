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

// a gcd of the Gaussian integers x = x.first + x.second i and y (unique up to the units 1, i, -1, -i); Euclid with the
// quotient rounded to the nearest Gaussian integer, so the remainder's norm at most halves; components up to ~1e18, O(log)
pll gaussian_gcd(pll x, pll y) {
    auto rdiv = [](__int128 a, __int128 b) {  // nearest integer to a / b for b > 0
        __int128 t = 2 * a + b, q = t / (2 * b);
        return t % (2 * b) && t < 0 ? q - 1 : q;
    };
    while (y.first || y.second) {
        __int128 n = (__int128)y.first * y.first + (__int128)y.second * y.second;
        __int128 re = rdiv((__int128)x.first * y.first + (__int128)x.second * y.second, n);  // x * conj(y) / n
        __int128 im = rdiv((__int128)x.second * y.first - (__int128)x.first * y.second, n);
        pll r((ll)(x.first - (re * y.first - im * y.second)), (ll)(x.second - (re * y.second + im * y.first)));
        x = y;
        y = r;
    }
    return x;
}

void solve() {
    ll t;
    cin >> t;
    while (t--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        auto [x, y] = gaussian_gcd({a, b}, {c, d});
        cout << x << " " << y << "\n";
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
