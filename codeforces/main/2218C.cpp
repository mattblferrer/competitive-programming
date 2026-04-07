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
    vector<ll> a(3*n);
    for (ll i = 0; i < n; i++) a[3*i] = i + 1;
    for (ll i = 0; i < n; i++) {
        a[3*i + 1] = n + 2*i + 1;
        a[3*i + 2] = n + 2*i + 2;
    }

    for (ll i = 0; i < 3*n; i++) cout << a[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}