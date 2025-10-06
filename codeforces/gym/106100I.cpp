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
    vector<vector<ll>> a(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }
    int mask = 0;
    for (int b = 26; b >= 0; b--) {
        vector<vector<ll>> dp(n, vector<ll>(n));
        int curr = 1 << b;
        dp[0][0] = a[0][0] & curr;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != 0) dp[i][j] = max(dp[i][j], dp[i - 1][j] & a[i][j] & curr);
                if (j != 0) dp[i][j] = max(dp[i][j], dp[i][j - 1] & a[i][j] & curr);
            }
        }
        if (dp[n - 1][n - 1]) mask += curr;
    }
    
    cout << mask;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}