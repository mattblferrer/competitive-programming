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
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> suff(n);
    suff[n - 1] = a[n - 1];
    for (ll i = n - 2; i >= 0; i--) {
        suff[i] = min(suff[i + 1], a[i]);
    }

    ll max_eq = 1, curr = 1;
    for (ll i = 0; i < n - 1; i++) {
        if (suff[i] == suff[i + 1]) curr++;
        else curr = 1;
        max_eq = max(max_eq, curr);
    }

    ll as = 0, suffs = 0;
    for (ll i = 0; i < n; i++) {
        as += a[i];
        suffs += suff[i];
    }
    ll ans = as - suffs + max_eq - 1;

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}