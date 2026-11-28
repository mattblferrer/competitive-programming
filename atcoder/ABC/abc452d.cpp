#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s, t;
    cin >> s >> t;
    ll n = s.size(), m = t.size();

    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1));

    for (ll i = 1; i <= n; i++) {
        for (ll j = 0; j <= m; j++) {
            if ((j == 0) && (s[i - 1] != t[0])) dp[i][j]++;
            if ((j == 1) && (s[i - 1] == t[0])) dp[i][j]++;
            if ((j < m) && (s[i - 1] != t[j])) dp[i][j] += dp[i - 1][j];
            if (s[i - 1] == t[j - 1]) dp[i][j] += dp[i - 1][j - 1];
        }
    }
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 0; j < m; j++) {
            ans += dp[i][j];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}