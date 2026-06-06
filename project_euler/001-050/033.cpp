#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll num = 1, den = 1;
    for (ll a = 10; a <= 99; a++) {
        for (ll b = a + 1; b <= 99; b++) {
            ll an, bn;
            if (a % 10 == b / 10) {
                an = a / 10, bn = b % 10;
            }
            else if (a / 10 == b % 10) {
                an = a % 10, bn = b / 10;
            }
            else continue;
            if (an * b == bn * a) {
                num *= a / gcd(a, b);
                den *= b / gcd(a, b);
            }
        }
    }
    cout << den / gcd(num, den);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}