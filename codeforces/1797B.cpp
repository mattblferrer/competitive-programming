#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt += (a[i][j] ^ a[n - i - 1][n - j - 1]);
        }
    }
    cnt /= 2;
    if (cnt <= k) {
        if (n % 2 == 1) cout << "YES\n";
        else if (cnt % 2 == k % 2) cout << "YES\n";
        else cout << "NO\n";
    }
    else cout << "NO\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}