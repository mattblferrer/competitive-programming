#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());
    ll ans = 0, x_sum = 0;
    for (ll i = 0; i < n; i++) {
        ll x = min(k - x_sum, m);
        ans += x * (x_sum + a[i]);
        x_sum += x;
        if (x_sum == k) break;
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