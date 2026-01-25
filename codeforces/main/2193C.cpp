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
    vector<ll> a(n + 2), b(n + 2);
    for (ll i = 1; i <= n; i++) cin >> a[i];
    for (ll i = 1; i <= n; i++) cin >> b[i];
    for (ll i = n; i > 0; i--) a[i] = max({a[i], b[i], a[i + 1]});
    vector<ll> pref(n + 2);
    for (ll i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];
    for (ll i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l - 1] << " ";
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}