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
    vector<ll> l(n + 1), p(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> l[i] >> p[i];
    }
    if (l[n] > n + 5) {
        cout << "-1\n";
        return;
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 5, INF));  // dp[monster][level] = min stamina
    dp[0][0] = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 0; j <= i; j++) {
            if (j < l[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = min({dp[i][j], dp[i - 1][j], dp[i - 1][j - 1] + p[i]});
        }
    }
    if (dp[n][l[n] - 1] == INF) cout << "-1\n";
    else cout << dp[n][l[n] - 1] + p[n] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
