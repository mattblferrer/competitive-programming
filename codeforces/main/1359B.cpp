#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

ll solve() {
    ll n, m, x, y;
    cin >> n >> m >> x >> y;
    vector<string> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (a[i][j] == '*') continue;  // black tile
            if (j == m - 1) ans += x;
            else if (a[i][j + 1] == '.' && 2 * x > y) {
                ans += y;
                j++;
            }
            else ans += x;
        }
    }
    return ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) cout << solve() << "\n";
    return 0;
}