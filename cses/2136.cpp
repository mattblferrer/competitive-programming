#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, k;
    cin >> n >> k;
    int ans = MOD;
    vector<bitset<32>> s(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        a[i] = s[i].to_ulong();
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i != j) ans = min(ans, __builtin_popcount(a[i] ^ a[j]));
        }
    }
    cout << ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}