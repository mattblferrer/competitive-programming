#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll ans = 0;
    for (ll i = n - 1; i > 0; i--) {
        ans += (a[i] + k - 1) / k;
        a[i] %= k;
        a[i - 1] = max(0LL, a[i - 1] - (k - a[i]) % k);
    }
    ans += (a[0] + k - 1) / k;
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}