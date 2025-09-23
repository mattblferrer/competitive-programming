#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> good;
    for (int i = 0; i < n; i++) {
        bool is_good = true;
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1 || a[i][j] == 3) is_good = false;
        }
        if (is_good) good.push_back(i + 1);
    }
    cout << good.size() << "\n";
    for (int i = 0; i < good.size(); i++) cout << good[i] << " ";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}