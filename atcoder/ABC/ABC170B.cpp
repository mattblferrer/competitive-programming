#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll x, y;
    cin >> x >> y;
    for (ll i = 0; i <= x; i++) {
        ll legs = 2 * i + 4 * (x - i);
        if (legs == y) {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}