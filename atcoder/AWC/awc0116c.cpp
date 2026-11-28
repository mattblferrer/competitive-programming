#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> h(n + 2);
    for (ll i = 1; i <= n; i++) cin >> h[i];

    ll ans = 0;
    vector<ll> peaks;
    for (ll i = 1; i <= n; i++) {
        if ((h[i - 1] < h[i]) && (h[i] >= h[i + 1])) peaks.push_back(i);
        else if ((h[i - 1] <= h[i]) && (h[i] > h[i + 1])) peaks.push_back(i);
    }
    for (ll p = 0; p < peaks.size(); p++) {
        ll idx = peaks[p];
        ll min_h = h[idx], max_h = h[idx], curr = 1;
        for (ll i = idx - 1; i >= 1; i--) {
            if (h[i] < h[i + 1]) {
                min_h = min(min_h, h[i]);
                curr++;
            }
            else break;
        }
        for (ll i = idx + 1; i <= n; i++) {
            if (h[i - 1] > h[i]) {
                min_h = min(min_h, h[i]);
                curr++;
            }
            else break;
        }
        if (max_h - min_h >= k) ans = max(ans, curr);
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}