#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll triangular(ll n) {
    return n * (n + 1) / 2;
}

bool is_pentagonal(ll n) {
    ld check = (sqrtl(24 * n + 1) + 1) / 6;
    return abs(check - round(check)) < 0.0000001;
}

bool is_hexagonal(ll n) {
    ld check = (sqrtl(8 * n + 1) + 1) / 4;
    return abs(check - round(check)) < 0.0000001;
}

void solve() {
    ll ctr = 286;
    while (true) {
        ll check = triangular(ctr);
        if (is_pentagonal(check) && is_hexagonal(check)) {
            cout << check;
            return;
        }
        ctr++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}