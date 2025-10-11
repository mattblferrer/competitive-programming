#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n), b(n);
    for (ll i = 0; i < n; i++) {
        cin >> b[i];
        if (b[i] == -1) {
            a[i] = x;
            b[i] = x;
        }
        else a[i] = b[i];
    }
    sort(a.begin(), a.end());
    if (a[n / 2] != x) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (ll i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}