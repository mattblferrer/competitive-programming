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
    vector<ll> f(n);
    for (ll i = 0; i < n; i++) cin >> f[i];
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) a[f[i] - 1] = i;
    ll ans = 0;
    for (ll i = 0; i < n - 1; i++) ans += abs(a[i + 1] - a[i]);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}