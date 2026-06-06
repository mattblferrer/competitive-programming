#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll ans = 1;
    for (ll i = 0; i * 2 < 1000; i++) {
        for (ll j = 0; j < 4; j++) ans += (2 * i + 3) * (2 * i + 3) - j * (2 * i + 2);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}