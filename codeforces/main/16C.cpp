#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, x, y;
    cin >> a >> b >> x >> y;
    ll g = gcd(x, y);
    x /= g; y /= g;

    ll left = 0, right = a + 1;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        ll midb = mid*y/x;
        if ((mid > a) || (midb > b)) right = mid; 
        else left = mid; 
    }
    cout << left/x*x << " " << left/x*y << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}