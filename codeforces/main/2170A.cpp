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
    vector<vector<ll>> a(n + 2, vector<ll>(n + 2));
    ll curr = 1;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            a[i][j] = curr;
            curr++; 
        }
    }
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            ans = max(ans, a[i][j] + a[i - 1][j] + a[i + 1][j] + a[i][j - 1] + a[i][j + 1]);
        }
    }
    cout << ans << '\n';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}