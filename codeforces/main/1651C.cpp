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
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];

    ll al = INF, bl = INF, ar = INF, br = INF;
    for (ll i = 1; i <= n - 1; i++) {
        al = min(al, abs(a[0] - b[i]));
        bl = min(bl, abs(a[i] - b[0]));
    }
    for (ll i = n - 2; i >= 1; i--) {
        ar = min(ar, abs(a[n - 1] - b[i]));
        br = min(br, abs(a[i] - b[n - 1]));
    }
    ll ans = min({
        abs(a[0] - b[0]) + abs(a[n - 1] - b[n - 1]),
        abs(a[0] - b[n - 1]) + abs(a[n - 1] - b[0]),
        abs(a[n - 1] - b[0]) + abs(a[n - 1] - b[n - 1]) + al,
        abs(a[0] - b[n - 1]) + abs(a[n - 1] - b[n - 1]) + bl,
        abs(a[0] - b[0]) + abs(a[0] - b[n - 1]) + ar,
        abs(a[0] - b[0]) + abs(a[n - 1] - b[0]) + br,
        abs(a[0] - b[0]) + ar + br,
        abs(a[0] - b[n - 1]) + ar + bl,
        abs(a[n - 1] - b[0]) + al + br,
        abs(a[n - 1] - b[n - 1]) + al + bl,
        al + bl + ar + br
        });

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}