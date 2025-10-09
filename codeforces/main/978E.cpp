#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, w;
    cin >> n >> w;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll minw = 0, maxw = 0, curr = 0;
    for (ll i = 0; i < n; i++) {
        curr += a[i];
        minw = min(minw, curr);
        maxw = max(maxw, curr);
    }
    ll ans = max(0LL, w - maxw + min(0LL, minw) + 1);
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}