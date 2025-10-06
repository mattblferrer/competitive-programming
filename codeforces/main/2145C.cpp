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
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') a++;
        else b++;
    }
    if (a == b) {
        cout << 0 << '\n';
        return;
    }
    int goal = b - a;
    vector<int> pref(n);
    map<int, int> idxs;
    int ans = n, p = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') p--;
        else p++;
        pref[i] = p;
        if (pref[i] == goal) ans = min(ans, i + 1);
        if (idxs.count(pref[i] - goal)) {
            int prev = idxs[pref[i] - goal];
            ans = min(ans, i - prev);
        }
        idxs[pref[i]] = i;
    }
    if (ans == n) cout << -1 << "\n";
    else cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}