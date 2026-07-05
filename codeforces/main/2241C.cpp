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

    ll min0 = 101, min1 = 101, max0 = -1, max1 = -1;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') {
            min0 = min(min0, i);
            max0 = max(max0, i);
        }
        else {
            min1 = min(min1, i);
            max1 = max(max1, i);
        }
    }
    if ((min0 == 101) || (min1 == 101)) cout << "1\n";
    else if ((max0 == min1 - 1) || (max1 == min0 - 1)) cout << "2\n";
    else cout << "1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}