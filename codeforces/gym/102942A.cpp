#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    ll angle = 36000000;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') angle += 90;
        else angle -= 90;
    }
    if (angle % 360 == 0) cout << "E\n";
    else if (angle % 360 == 90) cout << "S\n";
    else if (angle % 360 == 180) cout << "W\n";
    else cout << "N\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}