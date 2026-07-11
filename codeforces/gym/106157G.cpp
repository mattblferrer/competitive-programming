#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, a, b, x, y;
    cin >> n >> a >> b >> x >> y;
    ll wa = (x + y) * b;  // work all days
    ll tb = x * a;  // take break after x days
    ll ans = min(n, x) * a;

    ans += ((n - x) / (x + y)) * max(wa, tb);
    ll remain = ((n - x) % (x + y));
    wa = remain * b;
    tb = max(0LL, remain - y) * a;
    ans += max(wa, tb);

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}