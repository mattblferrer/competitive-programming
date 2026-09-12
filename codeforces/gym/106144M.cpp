#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') ans++;
    }
    for (int i = 1; i < n - 1; i++) {
        if ((s[i - 1] == '1') && (s[i] == '1') && (s[i + 1] == '1')) {
            ans -= 2;
            cout << ans << "\n";
            return;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if ((s[i] == '1') && (s[i + 1] == '1')) {
            ans--;
            cout << ans << "\n";
            return;
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