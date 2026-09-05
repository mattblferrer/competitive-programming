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

    vector<char> ans(n, 'C');
    ll zeros = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] == 0) {
            ans[i] = 'A' + (zeros % 2);
            zeros++;
        }
    }

    if (zeros != 1) {
        cout << "YES\n";
        for (ll i = 0; i < n; i++) cout << ans[i];
        cout << "\n";
    }
    else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}