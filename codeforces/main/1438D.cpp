#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll x = 0;
    for (ll i = 0; i < n; i++) x ^= a[i];
    if ((x != 0) && (n % 2 == 0)) {
        cout << "NO\n";
        return;
    }

    vector<vector<ll>> ops;
    ll limit;
    if (n % 2 == 1) limit = n;
    else limit = n - 1;
    for (ll i = 2; i < limit; i += 2) {
        ops.push_back({1, i, i + 1});
        ll curr = a[0] ^ a[i - 1] ^ a[i];
        a[0] = a[i - 1] = a[i] = curr;
    }
    for (ll i = 2; i < limit; i += 2) {
        ops.push_back({1, i, i + 1});
        ll curr = a[0] ^ a[i - 1] ^ a[i];
        a[0] = a[i - 1] = a[i] = curr;
    }

    cout << "YES\n";
    cout << ops.size() << "\n";
    for (ll i = 0; i < ops.size(); i++) {
        for (ll j = 0; j < 3; j++) cout << ops[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}