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
    vector<ll> t(n), a(n);
    for (ll i = 0; i < n; i++) {
        cin >> t[i];
    }
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll dp[n];
    memset(dp, 0, sizeof(dp));
    dp[n - 1] = a[n - 1];
    for (ll i = n - 2; i >= 0; i--) {
        dp[i] = min(t[i] + dp[i + 1], a[i] + 2 * dp[i + 1]);
    }
    cout << dp[0] << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}