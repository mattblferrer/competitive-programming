#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll l, r;
    cin >> l >> r;
    for (ll a = l; a <= r; a++) {
        for (ll b = a + 1; b <= r; b++) {
            for (ll c = b + 1; c <= r; c++) {
                if ((gcd(a, b) == 1) && (gcd(b, c) == 1) && (gcd(a, c) != 1)) {
                    cout << a << " " << b << " " << c << "\n";
                    return;
                }
            }
        }
    }
    cout << "-1\n";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}