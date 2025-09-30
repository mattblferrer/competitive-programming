#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

ll solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a <= b) return b;
    if (c <= d) return -1;
    ll ans = b + ((a - b + c - d - 1) / (c - d)) * c;
    return ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) cout << solve() << "\n";
    return 0;
}