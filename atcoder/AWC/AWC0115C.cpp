#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k, p;
    cin >> n >> k >> p;
    vector<ll> h(n);
    for (ll i = 0; i < n; i++) cin >> h[i];

    ll ans = 0;
    sort(h.begin(), h.end(), greater<ll>());
    for (ll i = 0; i < n; i++) {
        if (h[i] > 0) continue;
        ll avail = min(k, -h[i] / p + 1);
        h[i] += avail * p;
        k -= avail;
        if (k <= 0) break;
    }
    for (ll i = 0; i < n; i++) {
        if (h[i] <= 0) ans++;
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