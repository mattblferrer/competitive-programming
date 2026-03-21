#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q, c;
    cin >> n >> q >> c;
    vector<vector<vector<ll>>> stars(c + 1, vector<vector<ll>>(101, vector<ll>(101)));
    vector<vector<vector<ll>>> pref(c + 1, vector<vector<ll>>(101, vector<ll>(101)));
    for (ll i = 0; i < n; i++) {
        ll xi, yi, si;
        cin >> xi >> yi >> si;

        stars[si][xi][yi]++;
    }
    for (ll i = 0; i <= c; i++) {
        for (ll j = 1; j <= 100; j++) {
            for (ll k = 1; k <= 100; k++) {
                pref[i][j][k] = pref[i][j - 1][k] + pref[i][j][k - 1] - pref[i][j - 1][k - 1] + stars[i][j][k];
            }
        }
    } 
    for (ll i = 0; i < q; i++) {
        ll ti, x1, y1, x2, y2;
        cin >> ti >> x1 >> y1 >> x2 >> y2;

        ll ans = 0;
        for (ll j = 0; j <= c; j++) {
            ans += (pref[j][x2][y2] - pref[j][x1 - 1][y2] - pref[j][x2][y1 - 1] + pref[j][x1 - 1][y1 - 1]) * ((j + ti) % (c + 1));
        }
        cout << ans << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}