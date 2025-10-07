#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (n > 2) cout << "YES\n2\n" << s[0] << " " << s.substr(1, n - 1) << "\n";
    else if (s[0] < s[1]) cout << "YES\n2\n" << s[0] << " " << s[1] << "\n";
    else cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}