#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n, t, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t;
        ans += t * 3;
    }
    cout << ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}