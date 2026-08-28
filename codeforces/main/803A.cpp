#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (a[i][j] == 1) continue;
            if (k == 0) break;
            if ((i == j) && (k >= 1)) {
                a[i][j] = 1;
                k--;
            }
            else if (k >= 2) {
                a[i][j] = a[j][i] = 1;
                k -= 2;
            }
        }
    }
    if (k != 0) { cout << "-1\n"; return; }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    solve();
    return 0;
}