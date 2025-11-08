#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, v;
    cin >> n >> v;
    ll ans = n, k = n;
    for (ll i = 1; i <= n - v; i *= 2) {
        if (((n - v) & i) == 0) continue;
        k -= i;
        ans += k;
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