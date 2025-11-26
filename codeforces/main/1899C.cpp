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
    ll ans = -INF, curr = 0, prev = -1;
    for (ll i = 0; i < n; i++) {
        if ((curr > 0) && ((2 + a[i] % 2) % 2) != prev) {
            curr += a[i];
        }
        else {
            curr = a[i];
        }
        prev = (2 + a[i] % 2) % 2;
        ans = max(ans, curr);
    }
    cout << ans << '\n';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}