#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    ll n;
    cin >> n;
    ll ans = n;
    vector<ll> minus = {2, 3, 5, 7, 2 * 3 * 5, 2 * 3 * 7, 2 * 5 * 7, 3 * 5 * 7};
    vector<ll> plus = {2 * 3, 2 * 5, 2 * 7, 3 * 5, 3 * 7, 5 * 7, 2 * 3 * 5 * 7};
    for (ll d: minus) {
        ans -= n / d;
    }
    for (ll d: plus) {
        ans += n / d;
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