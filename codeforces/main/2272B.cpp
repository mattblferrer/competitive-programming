#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<string> grid(2);
    cin >> grid[0] >> grid[1];

    ll f0 = 0, f1 = 0;
    for (int i = 0; i < n; i++) {
        if (grid[0][i] == 'f') f0++;
        if (grid[1][i] == 'f') f1++;
    }
    ll ans = (f0 + f1) % 2;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}