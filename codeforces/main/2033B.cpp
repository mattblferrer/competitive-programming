#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> grid(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) cin >> grid[i][j];
    }
    map<ll, ll> diag_min;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            diag_min[i - j] = min(diag_min[i - j], grid[i][j]);
        }
    }
    ll ans = 0;
    for (auto& [s, m]: diag_min) {
        ans += max(0LL, -m);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}