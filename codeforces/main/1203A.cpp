#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> p(n);
    for (ll i = 0; i < n; i++) {
        cin >> p[i];
    }

    bool valid = true;
    for (ll i = 0; i < n - 1; i++) {
        if (((p[i + 1] % n) - (p[i] % n) + n) % n != 1) {
            valid = false;
        }
    }
    if (valid) {
        cout << "YES\n";
        return;
    }
    valid = true;
    for (ll i = 0; i < n - 1; i++) {
        if (((p[i] % n) - (p[i + 1] % n) + n) % n != 1) {
            valid = false;
        }
    }
    if (valid) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}