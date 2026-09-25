#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    vector<ll> l(3);
    for (ll i = 0; i < 3; i++) cin >> l[i];
    sort(l.begin(), l.end());
    if (l[0] == l[1]) {
        if (l[2] % 2 == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    else if (l[1] == l[2]) {
        if (l[0] % 2 == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    else if (l[0] + l[1] == l[2]) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}