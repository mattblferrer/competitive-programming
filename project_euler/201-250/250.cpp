#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 10'000'000'000'000'000;

ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

void solve() {
    vector<vector<ll>> dp(2, vector<ll>(250));
    dp[1][1] = 1;

    for (ll i = 2; i <= 250250; i++) {
        ll curr_mod = binexp(i, i, 250);
        for (ll j = 0; j < 250; j++) dp[i % 2][j] = 0;
        dp[i % 2][curr_mod]++;
        for (ll j = 0; j < 250; j++) {
            dp[i % 2][j] = (dp[i % 2][j] + dp[(i - 1) % 2][(j + 250 - curr_mod) % 250] + dp[(i - 1) % 2][j]) % MOD;
        }
    }
    cout << dp[0][0];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}