#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, s_i;
    cin >> n;
    multiset<int> s;
    for (int i = 0; i < n; i++) {
        cin >> s_i;
        s.insert(s_i);
    }
    for (int i = 1; i < 2048; i *= 2) {
        for (int j = 0; j < s.count(i) / 2; j++) {
            s.insert(2 * i);
        }
    }
    if (s.count(2048)) cout << "YES\n";
    else cout << "NO\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}