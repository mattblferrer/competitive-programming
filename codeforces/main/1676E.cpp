#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n), pref(n + 1);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<ll>());
    for (ll i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }
    for (ll i = 0; i < q; i++) {
        ll xi;
        cin >> xi;
        ll ans = distance(pref.begin(), upper_bound(pref.begin(), pref.end(), xi - 1));
        if (ans == n + 1) cout << "-1\n";
        else cout << ans << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}