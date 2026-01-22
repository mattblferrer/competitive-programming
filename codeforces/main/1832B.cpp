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
    vector<ll> a(n + 1), pref(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];
    sort(a.begin(), a.end());   
    for (ll i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }
    ll ans = 0;
    for (ll i = 0; i <= k; i++) {
        ans = max(ans, pref[n - (k - i)] - pref[2*i]);
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