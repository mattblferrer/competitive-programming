// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll l, r;
    cin >> l >> r;
    ll total = r - l + 1;
    ll ans = 0;
    if ((l <= 0) && (0 <= r)) {
        ans = total - 2 * min(abs(l), abs(r)) - 1;
        if (ans >= 1) ans--;
    }
    else {
        ans = total - 1;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}