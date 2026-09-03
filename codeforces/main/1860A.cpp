#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    string a = "", b = "";
    for (ll i = 0; i < n; i++) a += "()";
    for (ll i = 0; i < n; i++) b += '(';
    for (ll i = 0; i < n; i++) b += ')';

    bool match_a = false, match_b = false;
    for (ll i = 0; i < n; i++) {
        bool sub = true;
        for (ll j = i; j < i + n; j++) {
            if (s[j - i] != a[j]) {
                sub = false;
                break;
            }
        }
        if (sub) {
            match_a = true;
            break;
        }
    }
    for (ll i = 0; i < n; i++) {
        bool sub = true;
        for (ll j = i; j < i + n; j++) {
            if (s[j - i] != b[j]) {
                sub = false;
                break;
            }
        }
        if (sub) {
            match_b = true;
            break;
        }
    }
    if (!match_a) cout << "YES\n" << a << "\n";
    else if (!match_b) cout << "YES\n" << b << "\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}