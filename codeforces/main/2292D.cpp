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
    vector<ll> x(n), y(n);
    for (ll i = 0; i < n; i++) cin >> x[i];
    for (ll i = 0; i < n; i++) cin >> y[i];

    vector<vector<ll>> dp(2, vector<ll>(n + 1));  // turn 0 = sunny, 1 = aubrey
    for (ll i = n - 1; i >= 0; i--) {
        dp[0][i] = max(x[i] - y[i] + dp[0][i + 1], dp[1][i + 1]);
        dp[1][i] = min(y[i] - x[i] + dp[1][i + 1], dp[0][i + 1]);
    }
    if (dp[0][0] == dp[1][0]) cout << "Draw\n";
    else if (dp[0][0] > dp[1][0]) cout << "Sunny\n";
    else if (dp[0][0] < dp[1][0]) cout << "Aubrey\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
