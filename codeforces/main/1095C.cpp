#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    ll min_k = __builtin_popcountll(n);
    if ((k < min_k) || (k > n)) {
        cout << "NO\n";
        return;
    }
    map<ll, ll> cnt;
    for (ll i = 0; i < 32; i++) {
        if (n & (1LL << i)) cnt[1LL << i]++;
    }
    ll sz = cnt.size();
    while (sz < k) {
        ll f = cnt.rbegin()->first;
        cnt[f]--;
        cnt[f / 2] += 2;
        if (cnt[f] == 0) cnt.erase(f);
        sz++;
    }
    cout << "YES\n";
    for (const auto& [bi, c]: cnt) {
        for (ll i = 0; i < c; i++) cout << bi << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}