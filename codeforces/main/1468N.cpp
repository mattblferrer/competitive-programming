#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

string solve() {
    vector<ll> c(3), a(5);
    for (ll i = 0; i < 3; i++) cin >> c[i];
    for (ll i = 0; i < 5; i++) cin >> a[i];
    for (ll i = 0; i < 3; i++) {
        c[i] -= a[i];
        if (c[i] < 0) return "NO\n";
    }
    if (a[3] > c[0]) {
        a[3] -= c[0];
        c[0] = 0;
        c[2] -= a[3];
    }
    else {
        c[0] -= a[3];
        a[3] = 0;
    }
    if (a[4] > c[1]) {
        a[4] -= c[1];
        c[1] = 0;
        c[2] -= a[4];
    }
    else {
        c[1] -= a[4];
        a[4] = 0;
    }
    for (ll i = 0; i < 3; i++) {
        if (c[i] < 0) return "NO\n";
    }
    return "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) cout << solve();
    return 0;
}