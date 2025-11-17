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
    vector<ll> r(k);
    for (ll i = 0; i < k; i++) cin >> r[i];
    reverse(r.begin(), r.end());
    ll ans = n;
    for (ll i = 0; i < k; i++) {
        ans += r[i] * (1 << i);
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