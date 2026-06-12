#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, x;
    cin >> a >> b >> x;
    ll ans = INF, ctr = 0;
    while ((a > 0) || (b > 0)) {
        if (a > b) swap(a, b);
        ans = min(ans, b - a + ctr);
        b /= x;
        ctr++;
    }
    ans = min(ans, b - a + ctr);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}