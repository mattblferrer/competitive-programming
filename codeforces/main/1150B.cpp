#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> vdx = {-1, 0, 1, 0};
vector<ll> vdy = {0, -1, 0, 1};

void solve() {
    ll n;
    cin >> n;
    vector<string> grid(n);
    for (ll i = 0; i < n; i++) cin >> grid[i];
    for (ll i = 1; i < n - 1; i++) {
        for (ll j = 1; j < n - 1; j++) {
            bool valid = (grid[i][j] == '.');
            for (ll k = 0; k < 4; k++) {
                ll dx = vdx[k], dy = vdy[k];
                ll x = i + dx, y = j + dy;
                if (grid[x][y] == '#') valid = false;
            }
            if (!valid) continue;
            grid[i][j] = '#';
            for (ll k = 0; k < 4; k++) {
                ll dx = vdx[k], dy = vdy[k];
                ll x = i + dx, y = j + dy;
                grid[x][y] = '#';
            }
        }
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (grid[i][j] == '.') {
                cout << "NO\n";
                return;   
            }
        }
    }
    cout << "YES\n";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}