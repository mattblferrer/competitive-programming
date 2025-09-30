#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    ll n, q, l, r, k, sum = 0;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    vector<ll> pref(n + 1);
    for (ll i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }
    for (ll i = 0; i < q; i++) {
        cin >> l >> r >> k;
        ll sum_p = pref[r] - pref[l - 1];
        ll new_sum = sum - sum_p + k * (r - l + 1);
        if (new_sum % 2 == 0) cout << "NO\n";
        else cout << "YES\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}