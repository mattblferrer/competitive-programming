#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
 
int solve() {
    int x, y;
    cin >> x >> y;
    if (x < y) return 2;
    if (y > 1 && y + 2 <= x) return 3;
    return -1;
} 
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);
 
    int t; std::cin >> t; while (t--) cout << solve() << "\n";
    return 0;
}