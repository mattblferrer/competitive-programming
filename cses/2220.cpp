#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

long long dp[20][10][2][2];

ll count(string s, int pos, int last_d, bool leading, bool up) {
    if (pos == s.size()) return 1;
    if (dp[pos][last_d][leading][up] != -1) return dp[pos][last_d][leading][up];
    int limit;
    if (up) limit = s[pos] - '0';
    else limit = 9;

    ll ans = 0;
    for (int i = 0; i <= limit; i++) {
        if (leading && i == 0) {
            ans += count(s, pos + 1, 0, 1, 0);
            continue;
        }
        if (i == last_d) continue;
        if (i == limit) ans += count(s, pos + 1, i, 0, up);
        else ans += count(s, pos + 1, i, 0, 0);
    }
    return dp[pos][last_d][leading][up] = ans;
}

void solve() {
    ll a, b;
    cin >> a >> b;
    string a_str = to_string(a - 1), b_str = to_string(b);

    memset(dp, -1, sizeof(dp));
    ll b_ans = count(b_str, 0, 0, 1, 1);
    memset(dp, -1, sizeof(dp));
    ll a_ans = count(a_str, 0, 0, 1, 1);
    cout << b_ans - a_ans << '\n';
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}