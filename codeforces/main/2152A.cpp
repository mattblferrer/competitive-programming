#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, a_i;
    cin >> n;
    set<ll> a;
    for (ll i = 0; i < n; i++) {
        cin >> a_i;
        a.insert(a_i);
    }
    ll ans = a.size() * 2 - 1;
    cout << ans << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}