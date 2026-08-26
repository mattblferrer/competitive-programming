#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string symmetric = "AHIMOoTUVvWwXxY";
    map<char, char> s_pal = {
        {'b', 'd'}, {'d', 'b'}, {'p', 'q'}, {'q', 'p'}
    };
    string s;
    cin >> s;
    ll n = s.size();
    for (ll i = 0; i < s.size(); i++) {
        bool valid = false;
        for (char c : symmetric) {
            if ((s[i] == c) && (s[n - i - 1] == c)) { valid = true; break; }
        }
        if ((s[n - i - 1] == s_pal[s[i]])) valid = true;
        if (!valid) {
            cout << "NIE\n";
            return;
        }
    }
    cout << "TAK\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}