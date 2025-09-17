#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll ans = (i - 1) * (i + 4) * (i * (i - 3) + 4) / 2;
        cout << ans << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}