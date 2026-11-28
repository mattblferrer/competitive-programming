#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> ab(n + m);
    for (ll i = 0; i < n; i++) cin >> ab[i];
    for (ll i = n; i < n + m; i++) cin >> ab[i];

    sort(ab.begin(), ab.end(), greater<ll>());
    ll ans = 0;
    for (ll i = 0; i < k; i++) ans += ab[i];
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}