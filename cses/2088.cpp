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

vector<ll> pref;

ll cost(ll l, ll r) {
    return pref[r + 1] - pref[l];
}

ll base(ll n) {
    return 0;
}

// Knuth optimization, O(n^2): dp[i][j] = min over i <= k < j of dp[i][k] + dp[k + 1][j] + cost(i, j), dp[i][i] = base(i)
// requires opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]; returns the full dp table, the answer is usually dp[0][n - 1]
template <class Cost, class Base>
vector<vector<ll>> knuth_opt(int n, Cost cost, Base base) {
    vector<vector<ll>> dp(n, vector<ll>(n, INF));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = base(i);
        opt[i][i] = i;
        for (int j = i + 1; j < n; j++) {
            ll c = cost(i, j);
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                ll cur = dp[i][k] + dp[k + 1][j] + c;
                if (cur < dp[i][j]) {
                    dp[i][j] = cur;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    pref.resize(n + 1);
    for (ll i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i - 1];

    vector<vector<ll>> dp = knuth_opt(n, cost, base);
    cout << dp[0][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
