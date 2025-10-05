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
    int w = n, l = 0, ans = 0;
    while (true) {
        int wm = w / 2;
        int lm = l / 2;
        ans += wm + lm;
        l -= lm;
        l += wm;
        w -= wm;
        if (w == 1 && l == 1) break;
    }
    ans += 1;
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}