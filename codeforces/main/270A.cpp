#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a;
    cin >> a;
    for (ll s = 3; s <= 360; s++) {
        if (((s - 2) * 180) % s != 0) continue;
        if (((s - 2) * 180) / s == a) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}