#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> c(n, vector<ll>(m));
    vector<ll> col(n);
    for (int i = 0; i < n; i++) {
        ll col_min = INF;
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
            col_min = min(col_min, c[i][j]);
        }
        col[i] = col_min;
    }
    cout << *max_element(col.begin(), col.end());
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}