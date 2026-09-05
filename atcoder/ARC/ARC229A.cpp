#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

ll moves_num(string test) {
    ll test_ctr = 0;
    while (true) {
        bool move = false;
        for (ll i = 0; i < test.size() - 2; i++) {
            if (test[i] == 'A' && test[i + 1] == 'R' && test[i + 2] == 'C') {
                test[i] = 'C';
                test[i + 2] = 'A';
                test_ctr++;
                move = true;
                break;
            }
        }
        if (!move) return test_ctr;
    }
}

string solve(ll x) {
    string ans = "";
    if (x == 0) { return "ATCODER"; }
    if (x < 20) {
        for (ll i = 0; i < x; i++) ans += "ARC";
        return ans;
    }

    ll rt = (ll)sqrtl(x) + 1;
    for (ll i = 0; i < rt; i++) ans += "AR";
    ans += 'C';
    for (ll i = 0; i < rt - 1; i++) ans += "RC";

    ll leftover = moves_num(ans) - x;
    if (leftover >= rt) {
        ans[0] = 'C';
        leftover = moves_num(ans) - x;
    }
    ans[ans.size() - 2 * (rt - leftover - 1) - 1] = 'A';
    if (moves_num(ans) != x) {
        ans[ans.size() - 2 * (rt - leftover - 1) - 1] = 'C';
        ans[ans.size() - 2 * (rt - leftover) - 1] = 'A';
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    ll x;
    cin >> x;
    cout << solve(x);
    return 0;
}