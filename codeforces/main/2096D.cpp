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
    vector<pll> points(n);
    map<ll, ll> x, diag;
    for (ll i = 0; i < n; i++) {
        ll xi, yi;
        cin >> xi >> yi;
        points[i] = {xi, yi};
        x[xi]++;
        diag[xi + yi]++;
    }
    ll ansx = -1, ansy = -1;
    for (auto [xi, yi] : points) {
        if (x[xi] % 2 == 1) ansx = xi;
    }
    for (auto [xi, yi] : points) {
        if (diag[xi + yi] % 2 == 1) ansy = xi + yi - ansx;
    }
    cout << ansx << " " << ansy << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}