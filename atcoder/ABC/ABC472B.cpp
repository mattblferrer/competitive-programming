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
    vector<ll> l(n);
    for (ll i = 0; i < n; i++) cin >> l[i];

    ll left = 0, right = 0;
    for (ll i = 0; i < n; i++) right += l[i];
    ll ans = INF;
    for (ll i = 0; i < n; i++) {
        left += l[i];
        right -= l[i];
        ans = min(ans, abs(left - right));
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    solve();
    return 0;
}