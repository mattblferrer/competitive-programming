#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (ll i = 0; i < n; i++) cin >> grid[i];
    ll ans = 0;
    for (ll i = 0; i < n - 1; i++) {
        for (ll j = 0; j < m - 1; j++) {
            string chars;
            for (ll k = 0; k < 2; k++) {
                for (ll l = 0; l < 2; l++) {
                    chars.push_back(grid[i + k][j + l]);
                }
            }
            sort(chars.begin(), chars.end());
            if (chars == "acef") ans++;
        }
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}