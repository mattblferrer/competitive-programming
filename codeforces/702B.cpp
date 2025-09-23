#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;

void solve() {
    ll n, a_i;
    cin >> n;
    map<ll, ll> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a_i;
        cnt[a_i]++;
    }
    ll ans = 0;
    for (pll pair: cnt) {
        a_i = pair.first;
        ll freq = pair.second;
        for (int i = 0; i < 32; i++) {
            ll k = 1 << i;
            ll a_j = k - a_i;
            if (a_j < 0) continue;
            if (cnt.count(a_j)) {
                if (a_i == a_j) ans += freq * (cnt[a_j] - 1);
                else ans += freq * cnt[a_j];
            }
        }
    }
    cout << ans / 2;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}