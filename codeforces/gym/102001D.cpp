#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll r, c;

bool isCorner(ll row, ll col) {
    if ((row == 0) || (row == r-1)) {
        if ((col == 0) || (col == c-1)) {
            return true;
        }
    }
    return false;
}

bool isEdge(ll row, ll col) {
    if ((r <= 2) || (c <= 2)) {
        return false;
    }
    if ((row == 0) || (row == r-1)) {
        return true;   
    }
    if ((col == 0) || (col == c-1)) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    cin >> r >> c;
    bool hasEdge = false;
    ll count = 0;
    vector<vector<char>> grid(r, vector<char>(c));
    for (ll i = 0; i < r; i++) {
        for (ll j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }
    for (ll i = 0; i < r; i++) {
        for (ll j = 0; j < c; j++) {
            if (isCorner(i,j)) {
                
            } else if (isEdge(i,j)) {
                if (grid[i][j] == '#') {
                    hasEdge = true;
                }
            } else {
                if (grid[i][j] == '.') {
                    count++;
                }
            }
        }
    }
    if (!hasEdge && (r > 2) && (c > 2)) {
        count++;
    }
    if (r == 2 || c == 2) {
        ll count2 = 0;
        if (r == 2) {
            for (ll i = 1; i < c - 1; i++) {
                if ((grid[0][i] == '.') && (grid[1][i] == '.')) {
                    count2++;
                }
            }
        } else {
            for (ll i = 1; i < r - 1; i++) {
                if ((grid[i][0] == '.') && (grid[i][1] == '.')) {
                    count2++;
                }
            }
        }
        count = count2;
    }
    cout << count;
    return 0;
}