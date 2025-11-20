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
    vector<string> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end(), [](string a, string b) {
        return a.size() < b.size();
    });
    for (ll i = 0; i < n - 1; i++) {
        bool valid = false;
        for (ll j = 0; j < s[i + 1].size(); j++) {
            if (s[i + 1].substr(j, s[i].size()) == s[i]) {
                valid = true;
                break;
            }
        }
        if (!valid) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    for (ll i = 0; i < n; i++) cout << s[i] << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}