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
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> b[i];

    vector<ll> w(n);
    bool valid = false;
    for (ll i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            w[i] = 1e18;
            valid = true;
        }
        else w[i] = 1;
    }
    if (!valid) cout << "No\n";
    else {
        cout << "Yes\n";
        for (ll i = 0; i < n; i++) cout << w[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}