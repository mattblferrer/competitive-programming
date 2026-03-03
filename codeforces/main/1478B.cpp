#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll q, ai;
    char d;
    cin >> q >> d;
    vector<bool> is_lucky(100);
    for (ll i = 0; i < 100; i++) {
        string digits = to_string(i);
        for (ll j = 0; j < digits.size(); j++) {
            if (digits[j] == d) is_lucky[i] = true;
        }
    }
    vector<ll> lucky;
    for (ll i = 0; i < 100; i++) {
        if (is_lucky[i]) {
            lucky.push_back(i);
        }
    }
    vector<bool> ok(100);
    ok[0] = true;
    for (ll i = 0; i < 100; i++) {
        for (ll j = 0; j < lucky.size(); j++) {
            if (lucky[j] > i) continue;
            if (ok[i]) continue;
            ok[i] = ok[i - lucky[j]];
        }
    }
    for (ll i = 0; i < q; i++) {
        cin >> ai;
        if (ai >= 100) {
            cout << "YES\n";
        }
        else if (ok[ai]) {
            cout << "YES\n";
        }
        else cout << "NO\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}