#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll ab = a*b;
    for (ll x = a + 1; x <= c; x++) {
        ll g = gcd(x, ab);
        ll y = max(1LL, ab / g);
        ll left = -1, right = 1000000000;
        while (right - left > 1) {
            ll mid = (left + right) / 2;
            if (y*mid > d) right = mid; 
            else left = mid; 
        }
        y *= left;
        if (y <= b) continue;
        if (y > d) continue;
        cout << x << " " << y << "\n";
        return;
    }
    cout << "-1 -1\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}