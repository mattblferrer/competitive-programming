#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
        }
    }
    vector<set<int>> rows(n), cols(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            rows[i].insert(h[i][j]);
            cols[j].insert(h[i][j]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((rows[i].size() == 1) && (cols[j].size() == 1)) ans++;
        }
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}