#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, w;
    cin >> n >> w;
    vector<vector<ll>> dp(n + 1, vector<ll>(w + 1));
    map<ll, ll> weight, value;
    for (ll i = 1; i <= n; i++) {
        ll wi, vi;
        cin >> wi >> vi;
        weight[i] = wi;
        value[i] = vi;
    }

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= w; j++) {
            if (weight[i] > j) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
        }
    }
    cout << dp[n][w];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}