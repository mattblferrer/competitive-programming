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
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        sum += ai;
    }
    if (n == 1) {
        if (sum == 1) cout << "YES\n";
        else cout << "NO\n";
        return;
    }
    if (sum == n - 1) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}