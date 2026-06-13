#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    string s = "";
    while (s.size() < n) {
        for (ll i = 0; i < b; i++) s += 'a' + i;
        for (ll i = b; i < a; i++) s += 'a' + b - 1;
    }
    cout << s.substr(0, n) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}