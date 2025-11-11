#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ld n;
    cin >> n;
    vector<ld> r(n);
    for (ll i = 0; i < n; i++) cin >> r[i];
    ld ans = (r[0]*r[1]) / (r[0] + r[1]);
    for (ll i = 2; i < n; i++) {
        ans = (ans*r[i]) / (ans + r[i]);
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