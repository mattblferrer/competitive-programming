#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, r;
    cin >> a >> b >> r;
    if (a > b) swap(a, b);

    ll x = 0;
    bool highest = false;
    for (ll i = 63; i >= 0; i--) {
        ll shift = (1LL << i);
        if ((a & shift) != (b & shift)) {
            if (!highest) highest = true;
            else if (x + shift > r) continue;
            else if ((a & shift) == 0) x += shift;
        }
    }
    ll ans = abs((a ^ x) - (b ^ x));
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}