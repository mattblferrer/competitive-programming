#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];
    vector<vector<ll>> dp(n + 1, vector<ll>(2));
    string path = "";
    for (ll i = 1; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][0] + a[i], dp[i - 1][1] + a[i]);
        dp[i][1] = dp[i - 1][0] + 2*a[i];
    }
    ll act, curr = max(dp[n][0], dp[n][1]);
    for (ll i = n; i > 0; i--) {
        if (curr == dp[i][0]) act = 0;
        else act = 1;
        if (act == 0) {
            path += "O";
            curr -= a[i];
        }
        else {
            path += "M";
            curr -= 2*a[i];
        }
    }
    reverse(path.begin(), path.end());
    cout << max(dp[n][0], dp[n][1]) << "\n";
    cout << path;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}