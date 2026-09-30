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
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];

    ll max_a = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] > b[i]) swap(a[i], b[i]);
        max_a = max(max_a, a[i]);
    }
    ll ans = max_a;
    for (ll i = 0; i < n; i++) { 
        ans += b[i];
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