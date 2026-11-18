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
    ll n, w;
    cin >> n >> w;
    vector<pll> items(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll wi, vi;
        cin >> wi >> vi;
        items[i] = {wi, vi};
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(100'001, INF));
    dp[0][0] = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 0; j <= 100'000; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= items[i].second) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - items[i].second] + items[i].first);
            }
        }
    }

    ll ans = 0;
    for (ll i = 0; i <= 100'000; i++) {
        if (dp[n][i] <= w) ans = i;
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
