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

    vector<ll> b(n);
    b[0] = a[0];
    for (ll i = 1; i < n; i++) {
        if (i == n - 1) {
            b[i] = a[i];
            break;
        }
        else if (i == n - 2) {
            b[i] = a[i];
            b[i + 1] = a[i + 1];
            break;
        }
        else if (a[i] <= a[i + 1]) b[i] = a[i];
        else {
            b[i] = a[i + 1];
            b[i + 1] = a[i];
            b[i + 2] = a[i + 2];
            i += 2;
        }
    }

    for (ll i = 0; i < n; i++) cout << b[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}