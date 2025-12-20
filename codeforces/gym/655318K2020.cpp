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
    ll idx = 0, m = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] > m) {
            m = a[i];
            idx = i + 1;
        }
    }
    sort(a.begin(), a.end());
    for (ll i = 0; i < n - 1; i++) {
        if (a[n - 1] % a[i] != 0) {
            cout << -1;
            return;
        }
    }
    cout << idx;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}