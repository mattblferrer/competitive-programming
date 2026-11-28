#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    int dp[n][n][2];
    memset(dp, 0, sizeof(dp));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (i == j) dp[i][j][0] = dp[i][j][1] = 1;
            else if (i == j - 1) {
                if (s[i] == s[j]) dp[i][j][0] = 1;
                dp[i][j][1] = 1;
            }
            else if (s[i] == s[j]) {
                dp[i][j][0] = dp[i + 1][j - 1][0];
                dp[i][j][1] = dp[i + 1][j - 1][1];
            }
            else dp[i][j][1] = dp[i + 1][j - 1][0];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans += min(1, dp[i][j][0] + dp[i][j][1]);
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