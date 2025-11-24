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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n - 2; i++) {
        ll curr = a[i];
        a[i] -= curr;
        a[i + 1] -= 2*curr;
        a[i + 2] -= curr;
        if ((a[i] < 0) || (a[i + 1] < 0) || (a[i + 2] < 0)) {
            cout << "NO\n";
            return;
        }
    }
    for (ll i = 0; i < n; i++) {
        if (a[i] != 0) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}