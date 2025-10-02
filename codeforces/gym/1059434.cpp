#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        ll a_i;
        cin >> a_i;
        cnt[min(n + 1, a_i)]++;
    }
    map<ll, ll> pref;
    ll curr = 0;
    for (ll i = n + 1; i >= 0; i--) {
        pref[i] = pref[i + 1] + cnt[i];
    }
    ll lvl = 0;
    for (ll i = 1; i <= n + 1; i++) {
        if (pref[i] >= i) lvl = i;
        else break;
    }
    cout << lvl;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}