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
    int a = 0, b = 0, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') a++;
        else if (s[i] == ')' && a) {
            a--;
            ans++;
        }
        if (s[i] == '[') b++;
        else if (s[i] == ']' && b) {
            b--;
            ans++;
        }
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}