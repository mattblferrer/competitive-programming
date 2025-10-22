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
    int a = s.size(), b = t.size();
    int lc = lcm(a, b);
    string new_s = "", new_t = "";
    for (int i = 0; i < lc / a; i++) new_s += s;
    for (int i = 0; i < lc / b; i++) new_t += t;
    if (new_s == new_t) cout << new_s << '\n';
    else cout << "-1\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}