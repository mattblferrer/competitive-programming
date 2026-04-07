#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> a(7);
    for (ll i = 0; i < 7; i++) cin >> a[i];
    sort(a.begin(), a.end());
    for (ll i = 0; i < 6; i++) a[i] = -a[i];
    ll sum = 0;
    for (ll i = 0; i < 7; i++) sum += a[i];
    cout << sum << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}