#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    ll last = 0;
    vector<bool> eaten(n + 1);
    for (ll i = 1; i <= m; i++) {
        if (last + a[i] <= k) {
            cout << "Yes\n";
            last += a[i];
            eaten[i] = true;
        }
        else cout << "No\n";
    }
    for (ll i = m + 1; i <= n; i++) {
        if (eaten[i - m]) last -= a[i - m];
        if (last + a[i] <= k) {
            cout << "Yes\n";
            last += a[i];
            eaten[i] = true;
        }
        else cout << "No\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}