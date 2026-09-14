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
    int n = s.size();

    vector<int> rem(3, -2);
    rem[0] = -1;
    int curr = 0, prev = -1, ans = 0;
    for (ll i = 0; i < n; i++) {
        curr = (curr + s[i] - '0') % 3;
        if (rem[curr] >= prev) {
            ans++;
            prev = i;
        }
        rem[curr] = i;
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