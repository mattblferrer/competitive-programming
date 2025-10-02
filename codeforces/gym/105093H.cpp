#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pll> crystals;
    for (ll i = 0; i < n; i++) {
        ll c, r;
        cin >> c >> r;
        crystals.push_back({c, r});
    }
    ll ans = 0;
    for (ll i = 0; i < (1 << n); i++) {
        if (__builtin_popcount(i) != m) continue;
        map<ll, ll> used;
        for (ll j = 0; j < n; j++) {
            if (i & (1 << j)) used[crystals[j].first] += crystals[j].second;
        }
        ll curr = 1;
        for (const auto& pair: used) {
            curr *= pair.second;
        }
        ans = max(ans, curr);
    }
    cout << ans << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}