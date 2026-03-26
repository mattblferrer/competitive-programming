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
    string a;
    cin >> a;
    ll m;
    cin >> m;
    string b;
    cin >> b;
    string c;
    cin >> c;
    for (ll i = 0; i < m; i++) {
        if (c[i] == 'V') a = b[i] + a;
        else a = a + b[i];
    }
    cout << a << "\n";
 } 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}