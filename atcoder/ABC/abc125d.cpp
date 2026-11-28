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
    vector<ll> a(n);
    ll negs = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] < 0) negs++;
        a[i] = abs(a[i]);
    }
    ll ans = 0;
    sort(a.begin(), a.end());
    if (negs % 2 == 1) a[0] = -a[0];
    for (ll i = 0; i < n; i++) ans += a[i];

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}