#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool check(const vector<string>& grid) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            bool valid = true;
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    if (grid[i + k][j + l] == '.') valid = false;
                }
            }
            if (valid) return true;
            valid = true;
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    if (grid[i + k][j + l] == '#') valid = false;
                }
            }
            if (valid) return true;
        }
    }
    return false;
}

void solve() {
    vector<string> grid(4);
    for (int i = 0; i < 4; i++) cin >> grid[i];
    if (check(grid)) {
        cout << "YES\n";
        return;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {   
            vector<string> new_grid = grid;
            if (grid[i][j] == '.') new_grid[i][j] = '#';
            else new_grid[i][j] = '.';
            if (check(new_grid)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}