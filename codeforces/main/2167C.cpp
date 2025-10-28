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
    bool diff = false;
    for (ll i = 0; i < n - 1; i++) {
        if (a[i] % 2 != a[i + 1] % 2) diff = true;
    }
    if (diff) sort(a.begin(), a.end());
    for (ll i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}