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
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];
    
    vector<pll> ab(n);
    for (ll i = 0; i < n; i++) ab[i] = {a[i], b[i]};
    sort(ab.begin(), ab.end(), [](pll x, pll y) {
        return x.first + x.second > y.first + y.second;
    });
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (i % 2 == 0) ans += ab[i].first - 1;
        else ans -= ab[i].second - 1;
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