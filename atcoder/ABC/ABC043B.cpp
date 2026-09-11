#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string s;
    cin >> s;
    string ans = "";
    for (char c: s) {
        if (c == '0') ans += '0';
        else if (c == '1') ans += '1';
        else if (c == 'B') {
            if (!ans.empty()) ans.pop_back();
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}