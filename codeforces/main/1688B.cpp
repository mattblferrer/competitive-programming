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
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll min_p = INF, evens = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] % 2 == 0) evens++;
        ll curr = 0;
        while (a[i] % 2 == 0) {
            curr++;
            a[i] /= 2;
        }
        min_p = min(min_p, curr);
    }
    if (min_p > 0) evens--;
    if (evens > 0) cout << min_p + evens << "\n";
    else cout << min_p << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}