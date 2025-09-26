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
    vector<int> dp(101);
    for (int i = 0; i < 101; i++) {
        for (int j = 2; j <=7; j++) {
            if (i - j >= 0) {
                dp[i] = max(dp[i], dp[i - j] + 1);
            }
        }
    }
    for (int i = 0; i < t; i++) {
        int n; 
        cin >> n;
        cout << dp[n] << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;

    // bujbuj was here aichojij ^3^
}