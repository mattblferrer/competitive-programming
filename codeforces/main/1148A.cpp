#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    ll ans = 2 * c;
    if (a > b) ans += 2 * b + 1;
    else if (a < b) ans += 2 * a + 1;
    else ans += 2 * a;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}