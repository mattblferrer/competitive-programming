#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<ll> dp(1 << n);
    dp[0] = 1;
    for (ll i = 0; i < (1 << n); i++) {
        ll cnt = __builtin_popcountll(i);
        if (dp[i] == 0) continue;
        for (ll j = 0; j < n; j++) {
            if (1 & (i >> j)) continue;
            if (!a[cnt][j]) continue;
            ll next = i | (1 << j);
            dp[next] += dp[i];
            if (dp[next] >= MOD) dp[next] -= MOD;
        }
    }
    cout << dp[(1 << n) - 1] << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}