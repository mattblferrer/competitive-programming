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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll s1 = 0, s2 = 0;
    for (ll i = 0; i < n; i++) s2 += a[i];
    ll ans = s2 - s1;
    for (ll i = 0; i < n; i++) {
        s1 += a[i];
        s2 -= a[i];
        ans = min(ans, abs(s2 - s1));
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