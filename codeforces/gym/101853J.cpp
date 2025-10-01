#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, a_i;
    cin >> n;
    vector<int> cnt(10001);
    for (int i = 0; i < n; i++) {
        cin >> a_i;
        cnt[a_i]++;
    }
    int ans = 0;
    for (int i = 0; i < 10000; i++) {
        ans = max(ans, cnt[i] + cnt[i + 1]);
    }
    cout << ans << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}