#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    for (int i = 0; i < r; i++) {
        cin >> grid[i];
    }
    vector<pair<int, int>> points;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '#') points.push_back({i, j});
        }
    }
    int min_r = 101, max_r = 0;
    for (int i = 0; i <= 2; i++) {
        min_r = min(min_r, points[i].first);
        max_r = max(max_r, points[i].first);
    }
    sort(points.begin(), points.end(), [](auto a, auto b) {
        return a.second < b.second;
    });
    for (int i = min_r; i <= max_r; i++) {
        grid[i][points[1].second] = '#';
    }
    for (int i = points[0].second; i <= points[1].second; i++) {
        grid[points[0].first][i] = '#';
    }
    for (int i = points[2].second; i >= points[1].second; i--) {
        grid[points[2].first][i] = '#';
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << grid[i][j];
        }
        cout << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}