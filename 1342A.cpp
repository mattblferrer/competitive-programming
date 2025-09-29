#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll x, y, a, b;
    cin >> x >> y >> a >> b;
    if (a * 2 < b) {
        cout << a * (abs(x) + abs(y)) << "\n";
        return;
    }
    if ((x > 0) != (y > 0)) {
        cout << a * (abs(x) + abs(y)) << "\n";
        return;
    }
    if (abs(x) < abs(y)) {
        cout << b * abs(x) + a * (abs(y) - abs(x)) << "\n";
    }
    else {
        cout << b * abs(y) + a * (abs(x) - abs(y)) << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}