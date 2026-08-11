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
    vector<pll> pts(n);
    map<ll, ll> same_x, same_y, diag, antidiag;
    for (ll i = 0; i < n; i++) {
        ll xi, yi;
        cin >> xi >> yi;
        pts[i] = {xi, yi};
        same_x[xi]++;
        same_y[yi]++;
        diag[xi - yi]++;
        antidiag[xi + yi]++;
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll xi = pts[i].first, yi = pts[i].second;
        ans += same_x[xi] + same_y[yi] + diag[xi - yi] + antidiag[xi + yi] - 4;
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