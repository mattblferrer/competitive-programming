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
    vector<ll> first(26, -1);
    for (ll i = 0; i < s.size(); i++) {
        if (first[s[i] - 'a'] == -1) first[s[i] - 'a'] = i;
    }
    char c1 = 'z', c2 = 'z';
    ll minc = s.size();
    for (ll i = 0; i < 26; i++) {
        for (ll j = i - 1; j >= 0; j--) {
            if ((first[i] == -1) || (first[j] == -1)) continue;
            if (first[i] > first[j]) continue;
            if (first[i] <=  minc) {
                minc = first[i];
                c1 = 'a' + i, c2 = 'a' + j;
            }
        }
    }
    for (ll i = 0; i < s.size(); i++) {
        if (s[i] == c2) cout << c1;
        else if (s[i] == c1) cout << c2;
        else cout << s[i]; 
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