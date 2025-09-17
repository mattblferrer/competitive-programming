#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

string solve() {
    int a, b;
    cin >> a >> b;
    if ((a + b) % 3 != 0) return "NO";
    if (min(a, b) * 2 < max(a, b)) return "NO";
    return "YES";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; std::cin >> t; while (t--) std::cout << solve() << "\n";
    return 0;
}