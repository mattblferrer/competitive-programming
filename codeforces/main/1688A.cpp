#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll x;
    cin >> x;
    if (x == 1) {
        cout << "3\n";
        return;
    }
    for (ll y = 1; y <= x; y *= 2) {
        if (((x & y) > 0) && ((x ^ y) > 0)) {
            cout << y << "\n";
            return;
        }
    }
    cout << x + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}