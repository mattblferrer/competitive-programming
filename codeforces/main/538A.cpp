#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    string c = "CODEFORCES";
    for (ll i = 0; i < s.size(); i++) {
        for (ll j = i + 1; j <= s.size(); j++) {
            string ns = s.substr(0, i) + s.substr(j, s.size());
            if (ns == c) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}