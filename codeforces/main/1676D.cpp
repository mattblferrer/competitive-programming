#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> a[i][j];
    }

    map<ll, ll> diag1, diag2;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            diag1[j + i] += a[i][j];
            diag2[j - i] += a[i][j];
        }
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            ans = max(ans, diag1[j + i] + diag2[j - i] - a[i][j]);
        }
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