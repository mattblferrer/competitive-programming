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

    bool nonzero = false;
    for (ll i = 0; i < n; i++) {
        if (a[i] != 0) nonzero = true;
    }
    if (!nonzero) {
        cout << "0\n";
        return;
    }

    ll ans = 1;
    for (ll i = 0; i < n - 1; i++) {
        if (a[i] - 2 * a[i + 1] < 0) {
            cout << "-1\n";
            return;
        }
        ans = max(ans, a[i] - 2 * a[i + 1]);
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