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
    vector<ll> a(n), pref(n), suff(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    pref[0] = a[0];
    for (ll i = 1; i < n; i++) {
        pref[i] = gcd(a[i], pref[i - 1]);
    }
    suff[n - 1] = a[n - 1];
    for (ll i = n - 1; i >= 0; i--) {
        suff[i] = gcd(a[i], suff[i + 1]);
    }
    ll ans = pref[n - 1];
    for (ll i = 1; i < n - 1; i++) {
        ans += min(pref[i], suff[i]);
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}