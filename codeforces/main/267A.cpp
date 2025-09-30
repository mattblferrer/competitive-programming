#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    ll a, b, ans = 0;
    cin >> a >> b;
    if (a > b) swap(a, b);
    while (a != 0 && b != 0) {
        ll op = (b - a) / a + 1;
        ans += op;
        b -= op * a;
        swap(a, b);
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