#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    ll ans = 0;
    if (a > b) {
        ll diff = min(b, a - b);
        a -= diff*2;
        b -= diff;
        ans += diff;
        if (b > 0) ans += 2*min(a, b) / 3;
    }
    else {
        ll diff = min(a, b - a);
        a -= diff;
        b -= diff*2;
        ans += diff;
        if (a > 0) ans += 2*min(a, b) / 3;
    }
    cout << ans << '\n';
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}