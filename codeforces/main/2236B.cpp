#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for (int i = 0; i < n - k; i++) {
        if (s[i] == '1') {
            s[i] = '0';
            if (s[i + k] == '1') s[i + k] = '0';
            else s[i + k] = '1';
        }
    }
    for (int i = n - k; i < n; i++) {
        if (s[i] == '1') {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}