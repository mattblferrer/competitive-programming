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
    set<pll> pts;
    vector<ll> x0, x1;
    for (ll i = 0; i < n; i++) {
        ll xi, yi;
        cin >> xi >> yi;
        pts.insert({xi, yi});
        if (yi == 0) x0.push_back(xi);
        else x1.push_back(xi);
    }

    ll ans = 0;
    for (ll i = 0; i < x0.size(); i++) {
        if (pts.count({x0[i], 1})) ans += x0.size() - 1;
    }
    for (ll i = 0; i < x1.size(); i++) {
        if (pts.count({x1[i], 0})) ans += x1.size() - 1;
    }
    for (auto &[xi, yi] : pts) {
        if (yi == 0) {
            if ((pts.count({xi + 1, 1})) && (pts.count({xi + 2, 0}))) ans++;
        }
        else {
            if ((pts.count({xi + 1, 0})) && (pts.count({xi + 2, 1}))) ans++;
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