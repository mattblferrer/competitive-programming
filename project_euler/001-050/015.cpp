#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<vector<ll>> dp(22, vector<ll>(22));
    dp[1][1] = 1;
    for (ll i = 1; i <= 21; i++) {
        for (ll j = 1; j <= 21; j++) {
            dp[i][j] = dp[i][j] + dp[i - 1][j] + dp[i][j - 1];
        }
    }
    cout << dp[21][21];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}