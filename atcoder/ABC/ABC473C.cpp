#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> classes(k + 1);
    for (ll i = 0; i < n; i++) classes[a[i]]++;

    ll max_class = 0;
    for (ll i = 1; i <= k; i++) {
        max_class = max(max_class, classes[i]);
    }
    ll ans = 0;
    for (ll i = 1; i <= k; i++) {
        if (classes[i] + 1 >= max_class) {
            ans++;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}