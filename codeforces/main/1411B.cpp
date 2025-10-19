#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_fair(ll n) {
    string digits = to_string(n);
    for (int d: digits) {
        if ((d - '0') == 0) continue;
        if (n % (d - '0') != 0) return false;
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;
    while (true) {
        if (is_fair(n)) {
            cout << n << "\n";
            return;
        }
        n++;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}