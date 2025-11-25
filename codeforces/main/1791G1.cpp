#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, c;
    cin >> n >> c;
    vector<ll> a(n + 1);
    a[n] = INF;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += (i + 1);
    }
    sort(a.begin(), a.end());
    ll curr = 0;
    for (ll i = 0; i <= n; i++) {
        curr += a[i];
        if (curr > c) {
            cout << i << "\n";
            return;
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}