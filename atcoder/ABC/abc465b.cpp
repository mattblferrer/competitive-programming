#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll x, y, l, r, a, b;
    cin >> x >> y >> l >> r >> a >> b;
    ll ans = 0;
    for (ll i = a; i < b; i++) {
        if ((l <= i) && (i < r)) ans += x;
        else ans += y;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}