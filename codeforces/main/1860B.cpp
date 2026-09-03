#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll m, k, a1, ak;
    cin >> m >> k >> a1 >> ak;

    ll ans = 0;
    ll curr = a1 - (a1 % k) + m % k;
    if (curr > a1) curr -= k;
    if (curr < 0) {
        curr += k;
        ans += curr - a1;
    }

    curr += k * ak;
    if (curr >= m) {
        cout << ans << "\n";
        return;
    }
    else {
        cout << ans + (m - curr) / k << "\n";
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}