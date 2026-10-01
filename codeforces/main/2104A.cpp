#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    if ((a + b + c) % 3 != 0) {
        cout << "NO\n";
        return;
    }
    ll need = (a + b + c) / 3;
    if ((a > need) || (b > need)) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}