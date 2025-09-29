#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    if (m <= n / k) {
        cout << m << "\n";
        return;
    }
    m -= n / k;
    vector<int> hands(k - 1);
    for (int i = 0; i < m; i++) {
        hands[i % (k - 1)]++;
    }
    cout << n / k - hands[0] << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}