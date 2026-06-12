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
    vector<ll> h(n);
    for (ll i = 0; i < n; i++) cin >> h[i];
    ll min_h = INF, max_h = 0;
    for (ll i = 0; i < n; i++) {
        min_h = min(min_h, h[i]);
        max_h = max(max_h, h[i]);
    }
    cout << max_h - min_h + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}