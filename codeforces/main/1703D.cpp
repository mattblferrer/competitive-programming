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
    vector<string> s_vec(n);
    set<string> s_set;
    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        s_vec[i] = s;
        s_set.insert(s);
    }
    for (ll i = 0; i < n; i++) {
        string s = s_vec[i];
        bool valid = false;
        for (ll j = 1; j < s.size(); j++) {
            string s1 = s.substr(0, j);
            string s2 = s.substr(j, s.size() - j);
            if (s_set.count(s1) && s_set.count(s2)) valid = true;
        }
        cout << (valid ? "1" : "0");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}