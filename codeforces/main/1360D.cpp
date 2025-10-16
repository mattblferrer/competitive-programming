#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, k;
    cin >> n >> k;
    set<int> factors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i <= k) factors.insert(i);
            if ((n / i) <= k) factors.insert(n / i);
        }
    }
    int ans = MOD;
    for (int f: factors) {
        ans = min(ans, n / f);
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