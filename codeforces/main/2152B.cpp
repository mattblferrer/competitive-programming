#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, rk, ck, rd, cd;
    cin >> n >> rk >> ck >> rd >> cd;
    ll ans = 0;
    if (rk < rd) ans = rd;
    else if (rk > rd) ans = n - rd;
    if (ck < cd) ans = max(ans, cd);
    else if (ck > cd) ans = max(ans, n - cd);
    cout << ans << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}