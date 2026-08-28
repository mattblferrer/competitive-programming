#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (ll i = 0; i < h; i++) cin >> grid[i];

    vector<vector<ll>> dp(h, vector<ll>(w));
    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            if ((i == 0) && (j == 0)) dp[i][j] = (grid[i][j] == '#');
            else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + ((grid[i][j - 1] == '.') && (grid[i][j] == '#'));
            }
            else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + ((grid[i - 1][j] == '.') && (grid[i][j] == '#'));
            }
            else {
                dp[i][j] = min(
                    dp[i][j - 1] + ((grid[i][j - 1] == '.') && (grid[i][j] == '#')),
                    dp[i - 1][j] + ((grid[i - 1][j] == '.') && (grid[i][j] == '#'))
                );
            }
        }
    }
    cout << dp[h - 1][w - 1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}