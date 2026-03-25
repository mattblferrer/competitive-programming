#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll number_factors(ll n) {
    ll ans = 1;
    while (n % 2 == 0) {
        ans++;
        n /= 2;
    }
    for (ll i = 3; i*i <= n; i += 2) {
        ll power = 1;
        while (n % i == 0) {
            power++;
            n /= i;
        }
        ans *= power;
    }
    if (n != 1) ans *= 2;
    return ans;
}

void solve() {
    ll tri = 1, ctr = 2;
    while (number_factors(tri) <= 500) {
        tri += ctr;
        ctr++;
    }
    cout << tri;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}