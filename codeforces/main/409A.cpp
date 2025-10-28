#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s, t;
    cin >> s >> t;
    ll t1 = 0, t2 = 0;
    for (int i = 0; i < s.size(); i += 2) {
        if (s[i] == '[') {
            if (t[i] == '(') t1++;
            if (t[i] == '8') t2++;
        }
        if (s[i] == '(') {
            if (t[i] == '8') t1++;
            if (t[i] == '[') t2++;
        }
        if (s[i] == '8') {
            if (t[i] == '[') t1++;
            if (t[i] == '(') t2++;
        }
    }
    if (t1 > t2) cout << "TEAM 1 WINS";
    else if (t1 < t2) cout << "TEAM 2 WINS";
    else cout << "TIE";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}