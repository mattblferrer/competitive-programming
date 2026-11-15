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

struct Friend {
    ll x, y, v, i;
};

void solve() {
    ll n;
    cin >> n;
    vector<Friend> f(n);
    for (ll i = 0; i < n; i++) {
        ll x, y, v;
        cin >> x >> y >> v;
        f[i] = {x, y, v, i};
    }
    ld left1 = 0, right1 = 1e7;
    for (ll it = 0; it < 100; it++) {
        ld t = (left1 + right1) / 2, max1 = -INF, max2 = -INF;
        for (ll i = 0; i < n; i++) {
            max1 = max(max1, f[i].x + f[i].y - t * f[i].v);
        }
        for (ll i = 0; i < n; i++) {
            max2 = max(max2, -f[i].x - f[i].y - t * f[i].v);
        }
        if (max1 + max2 >= 0) left1 = t;
        else right1 = t;
    }

    ld left2 = 0, right2 = 1e7;
    for (ll it = 0; it < 100; it++) {
        ld t = (left2 + right2) / 2, max1 = -INF, max2 = -INF;
        for (ll i = 0; i < n; i++) {
            max1 = max(max1, f[i].x - f[i].y - t * f[i].v);
        }
        for (ll i = 0; i < n; i++) {
            max2 = max(max2, -f[i].x + f[i].y - t * f[i].v);
        }
        if (max1 + max2 >= 0) left2 = t;
        else right2 = t;
    }

    cout << max(left1, left2) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
