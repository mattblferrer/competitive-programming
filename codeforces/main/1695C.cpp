#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> a[i][j];
    }
    if ((n + m) % 2 == 0) {
        cout << "NO\n";
        return;
    }
    vector<vector<ll>> min_dp(n, vector<ll>(m, INF)), max_dp(n, vector<ll>(m, -INF));
    min_dp[0][0] = max_dp[0][0] = a[0][0];
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if ((i == 0) && (j == 0)) continue;
            if (i != 0) {
                min_dp[i][j] = min(min_dp[i][j], min_dp[i - 1][j] + a[i][j]);
                max_dp[i][j] = max(max_dp[i][j], max_dp[i - 1][j] + a[i][j]);
            }
            if (j != 0) {
                min_dp[i][j] = min(min_dp[i][j], min_dp[i][j - 1] + a[i][j]);
                max_dp[i][j] = max(max_dp[i][j], max_dp[i][j - 1] + a[i][j]);
            }
        }
    }
    if ((min_dp[n - 1][m - 1] <= 0) && (max_dp[n - 1][m - 1] >= 0)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}