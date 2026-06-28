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
    string s;
    cin >> n >> s;
    bool has_l_or_v = false, has_lv = false;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'l') has_l_or_v = true;
        if (s[i] == 'v') has_l_or_v = true;
        if (s.substr(i, 2) == "lv") has_lv = true;
    }
    if (has_lv) cout << "0\n";
    else if (has_l_or_v) cout << "1\n";
    else cout << "2\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}