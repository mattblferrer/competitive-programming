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

void solve() {
    ll n;
    cin >> n;
    vector<ll> p(n);
    for (ll i = 0; i < n; i++) cin >> p[i];

    ll ans = INF;
    for (ll mask = 0; mask < (1 << n); mask++) {
        ll a = 0, b = 0;
        for (ll i = 0; i < n; i++) {
            if (mask & (1 << i)) a += p[i];
            else b += p[i];
        }
        ans = min(ans, abs(a - b));
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
