#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

/**
 * For any given integer m and n, m > n > 0: 
 * a = m^2 - n^2
 * b = 2mn
 * c = m^2 + n^2,
 * is a valid Pythagorean triple
 */

void solve() {
    ll sum_abc = 1000;
    ll limit = 100;
    for (ll m = 1; m < limit; m++) {
        for (ll n = 1; n < m; n++) {
            ll a = m*m - n*n;
            ll b = 2*m*n;
            ll c = m*m + n*n;
            if (a + b + c == sum_abc) {
                cout << a*b*c;
                return;
            }
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}