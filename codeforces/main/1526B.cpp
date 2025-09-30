#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int t;
    cin >> t;
    bool dp[1101];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i <= 1100; i++) {
        if (i >= 11 && dp[i - 11]) dp[i] = 1;
        if (i >= 111 && dp[i - 111]) dp[i] = 1;
    }
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        if (n > 1100) cout << "YES\n";
        else {
            if (dp[n]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}