#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    char t;
    cin >> t;
    string a, b;
    cin >> a >> b;
    map<char, int> m = {
        {'6', 0}, {'7', 1}, {'8', 2}, {'9', 3}, {'T', 4},
        {'J', 5}, {'Q', 6}, {'K', 7}, {'A', 8}
    };
    if (a[1] == t && b[1] != t) cout << "YES\n";
    else if (a[1] != t && b[1] == t) cout << "NO\n";
    else if (a[1] != b[1]) cout << "NO\n";
    else if (m[a[0]] < m[b[0]]) cout << "NO\n";
    else cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}