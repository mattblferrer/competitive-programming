#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    map<ll, ll> fac;
    for (ll i = 2; i*i <= n; i++) {
        while (n % i == 0) {
            fac[i]++;
            n /= i;
        }
    }
    if (n != 1) fac[n]++;
    ll max_p = 0;
    for (auto pair: fac) {
        max_p = max(max_p, pair.second);
    }
    ll ans = 0;
    for (ll i = 0; i < max_p; i++) {
        ll curr = 1;
        for (auto pair: fac) {
            if (pair.second > 0) {
                curr *= pair.first;
                fac[pair.first]--;
            }
        }
        ans += curr;
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