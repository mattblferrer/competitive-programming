#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n % 2 == 0) cout << "2 " << n - 3 << " 1\n";
    else {
        for (int i = 1; i <= n / 2; i++) {
            if (gcd(n / 2 - i, n / 2 + i) == 1) {
                cout << n / 2 - i << " " << n / 2 + i << " 1\n";
                return;
            }
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}