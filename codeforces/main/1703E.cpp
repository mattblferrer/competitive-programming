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
    vector<string> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            ll curr = 0;
            if (a[i][j] == '1') curr++;
            if (a[n - i - 1][n - j - 1] == '1') curr++;
            if (a[n - j - 1][i] == '1') curr++;
            if (a[j][n - i - 1] == '1') curr++;
            ans += min(curr, 4 - curr);
        }
    }
    ans /= 4;

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}