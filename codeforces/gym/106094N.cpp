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
    vector<ll> a(n), b(n), c(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];
    for (ll i = 0; i < n; i++) cin >> c[i];
    ll diffa = 0, diffb = 0;
    for (ll i = 0; i < n; i++) {
        if ((a[i] - c[i]) % 2 != 0) {
            cout << "NO\n";
            return;
        }
        if (a[i] < c[i]) {
            cout << "NO\n";
            return;
        }
        diffa += a[i] - c[i];
    }
    for (ll i = 0; i < n; i++) {
        if (b[i] > c[i]) {
            cout << "NO\n";
            return;
        }
        diffb += c[i] - b[i];
    }
    if (diffb * 2 == diffa) cout << "YES\n";
    else cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}