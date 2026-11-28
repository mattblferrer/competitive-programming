#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (ll i = 0; i < h; i++) cin >> grid[i];
    ll min_h = INF, max_h = -1, min_w = INF, max_w = -1;
    for (ll i = 0; i < h; i++) {
        for (ll j = 0; j < w; j++) {
            if (grid[i][j] == '#') {
                min_h = min(min_h, i);
                max_h = max(max_h, i);
                min_w = min(min_w, j);
                max_w = max(max_w, j);
            }
        }
    }
    for (ll i = min_h; i <= max_h; i++) {
        for (ll j = min_w; j <= max_w; j++) {
            if (grid[i][j] == '.') {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}