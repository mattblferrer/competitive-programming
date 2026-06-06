#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> factorials = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

ll factorial_digsum(ll n) {
    ll ans = 0;
    while (n > 0) {
        ans += factorials[n % 10];
        n /= 10;
    }
    return ans;
}

void solve() {
    ll ans = 0;
    for (ll i = 10; i < 7 * 362880; i++) {
        if (factorial_digsum(i) == i) ans += i;
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