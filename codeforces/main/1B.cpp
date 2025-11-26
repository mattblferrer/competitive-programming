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
    ll group = 0;
    for (ll i = 1; i < s.size(); i++) {
        if ((!isalpha(s[i])) && (isalpha(s[i - 1]))) group++;
    }
    if (group == 1) {
        string coltext = "", rowtext = "";
        for (ll i = 0; i < s.size(); i++) {
            if (isalpha(s[i])) coltext += s[i];
            else rowtext += s[i];
        }
        ll col = 0, row = stoll(rowtext);
        ll exp = 1;
        for (ll i = coltext.size() - 1; i >= 0; i--) {
            col += (s[i] - 'A' + 1)*exp;
            exp *= 26;
        }
        cout << "R" << row << "C" << col << "\n";
    }
    else {
        string coltext = "", rowtext = "";
        ll g = 0;
        for (ll i = 0; i < s.size(); i++) {
            if (isalpha(s[i])) g++;
            else if (g == 1) rowtext += s[i];
            else coltext += s[i];
        }
        ll col = stoll(coltext), row = stoll(rowtext);
        string newcol = "";
        while (col > 0) {
            col--;
            newcol += (char)(col % 26 + 'A');
            col /= 26;
        }
        reverse(newcol.begin(), newcol.end());
        cout << newcol << row << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}