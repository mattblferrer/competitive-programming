#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll a1 = 13, b1 = 42, c1 = 14;
    ll a2 = 17, b2 = 69, c2 = 7;
    for (ll k = 1; k <= 226969; k++) {
        cout << k * k * k * a1 << " " << k * b1 << " " << k * k * c1 << "\n";
    }
    for (ll k = 1; k <= 200000; k++) {
        cout << k * k * k * a2 << " " << k * b2 << " " << k * k * c2 << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}