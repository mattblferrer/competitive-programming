#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    double n, r;
    cin >> n >> r;
    double ans = n * pow(r, 2) / (1 / tan(M_PI / (2 * n)) + 1 / tan(M_PI / n));
    cout << ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}