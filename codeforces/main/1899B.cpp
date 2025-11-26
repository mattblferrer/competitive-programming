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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    set<ll> factors;
    for (ll i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            factors.insert(i);
            factors.insert(n / i);
        }
    }
    ll ans = 0;
    for (ll f: factors) {
        ll low = INF, high = 0;
        for (ll i = 0; i*f < n; i++) {
            ll curr = 0;
            for (ll j = i*f; j < (i + 1)*f; j++) curr += a[j];
            low = min(low, curr);
            high = max(high, curr);
        }
        ans = max(ans, high - low);
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