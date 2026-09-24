#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, ax, ay, bx, by;
    cin >> n >> ax >> ay >> bx >> by;
    vector<pll> pts(n);
    for (ll i = 0; i < n; i++) {
        ll xi;
        cin >> xi;
        pts[i].first = xi;
    }
    for (ll i = 0; i < n; i++) {
        ll yi;
        cin >> yi;
        pts[i].second = yi;
    }
    pts.push_back({bx, by});
    n++;
    sort(pts.begin(), pts.end());

    map<ll, ll> min_y, max_y;
    for (ll i = 0; i < n; i++) {
        const auto [xi, yi] = pts[i];
        if (min_y.count(xi) == 0) {
            min_y[xi] = yi;
            max_y[xi] = yi;
        }
        else {
            min_y[xi] = min(min_y[xi], yi);
            max_y[xi] = max(max_y[xi], yi);
        }
    }

    vector<ll> curr = {ay, ay};
    vector<vector<ll>> dp(1, vector<ll>(2));
    ll ctr = 1;

    for (const auto &[xi, min_yi] : min_y) {
        ll max_yi = max_y[xi];
        dp.push_back({0, 0});
        dp[ctr][0] = min(
            dp[ctr - 1][0] + abs(curr[0] - min_yi) + (max_yi - min_yi),
            dp[ctr - 1][1] + abs(curr[1] - min_yi) + (max_yi - min_yi)
        );  // down first
        dp[ctr][1] = min(
            dp[ctr - 1][0] + abs(curr[0] - max_yi) + (max_yi - min_yi),
            dp[ctr - 1][1] + abs(curr[1] - max_yi) + (max_yi - min_yi)
        );  // up first
        curr[0] = max_yi;
        curr[1] = min_yi;
        ctr++;
    }
    cout << min(dp.back()[0], dp.back()[1]) + bx - ax << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}