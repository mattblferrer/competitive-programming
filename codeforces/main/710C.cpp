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
    vector<vector<ll>> sq(n, vector<ll>(n));
    ll curr = 1;
    for (ll i = 0; i <= n / 2; i++) {
        for (ll j = n / 2 - i; j <= n / 2 + i; j++) {
            sq[i][j] = curr;
            curr += 2;
        }
    }
    for (ll i = 0; i < n / 2; i++) {
        for (ll j = i + 1; j < n - i - 1; j++) {
            sq[i + n / 2 + 1][j] = curr;
            curr += 2;
        }
    }
    curr = 2;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (sq[i][j] == 0) {
                sq[i][j] = curr;
                curr += 2;
            }
        }
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cout << sq[i][j] << " ";
        }
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