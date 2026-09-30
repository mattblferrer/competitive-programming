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
    if (n == 2) {
        cout << "-1\n";
        return;
    }
    vector<ll> ans(n * n);
    ll pos = 0, curr = 1;
    while (pos < n * n) {
        ans[pos] = curr;
        pos += 2;
        curr++;
    }
    pos = 1;
    while (pos < n * n) {
        ans[pos] = curr;
        pos += 2;
        curr++;
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cout << ans[i * n + j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}