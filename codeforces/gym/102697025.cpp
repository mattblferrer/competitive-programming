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
    ll n;
    cin >> n;
    vector<string> dict(n);
    for (ll i = 0; i < n; i++) {
        cin >> dict[i];
    }
    ll minc = s.size() + 1;
    string w;
    for (ll i = 0; i < n; i++) {
        if (dict[i].size() != s.size()) continue;
        ll curr = 0;
        for (ll j = 0; j < s.size(); j++) {
            if (s[j] != dict[i][j]) curr++;
        }
        if (curr < minc) {
            w = dict[i];
            minc = curr;
        }
    }
    cout << w;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}