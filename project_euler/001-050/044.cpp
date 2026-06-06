#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll pentagonal(ll n) {
    return n * (3 * n - 1) / 2;
}

bool is_pentagonal(ll n) {
    ld check = (sqrtl(24 * n + 1) + 1) / 6;
    return abs(check - round(check)) < 0.0000001;
}

void solve() {
    ll min_diff = INF;
    for (ll i = 1; i < 10000; i++) {
        for (ll j = i + 1; j < 10000; j++) {
            ll pi = pentagonal(i), pj = pentagonal(j);
            if (is_pentagonal(pj - pi) && is_pentagonal(pj + pi)) {
                min_diff = min(min_diff, pj - pi);
            }
        }
    }
    cout << min_diff;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}