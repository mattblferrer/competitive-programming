#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int curr = 0;
    string ans = "";
    for (int i = 0; i < n; i++) {
        int up = 'z' - s[i], down = s[i] - 'a';
        if (up > down) {
            if (k - curr < up) {
                ans += s[i] + (k - curr);
                curr = k;
            }
            else {
                ans += 'z';
                curr += up;
            }
        }
        else {
            if (k - curr < down) {
                ans += s[i] - (k - curr);
                curr = k;
            }
            else {
                ans += 'a';
                curr += down;
            }
        }
    }
    if (curr != k) cout << "-1\n";
    else cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}