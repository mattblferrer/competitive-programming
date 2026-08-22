#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> vals(3, vector<ll>(n + 1));
    for (ll i = 0; i < 3; i++) {
        for (ll j = 1; j <= n; j++) cin >> vals[i][j];
    }

    ll total = 0;
    for (ll j = 1; j <= n; j++) total += vals[0][j];
    ll share = (total + 2) / 3;

    vector<ll> perm = {0, 1, 2};
    bool possible = false;
    do {
        vector<ll> sum(3);
        vector<pll> ans(3, {-1, -1});
        for (ll j = 1; j <= n; j++) {
            sum[0] += vals[perm[0]][j];
            if (sum[0] >= share) {
                ans[perm[0]] = {1, j};
                break;
            }
        }
        for (ll j = n; j >= 1; j--) {
            sum[2] += vals[perm[2]][j];
            if (sum[2] >= share) {
                ans[perm[2]] = {j, n};
                break;
            }
        }

        ans[perm[1]] = {ans[perm[0]].second + 1, ans[perm[2]].first - 1};
        for (ll j = ans[perm[1]].first; j <= ans[perm[1]].second; j++) {
            sum[1] += vals[perm[1]][j];
        }

        if (sum[1] < share) {
            continue;
        }
        possible = true;
        for (ll i = 0; i < 3; i++) {
            cout << ans[i].first << " " << ans[i].second << " ";
        }
        cout << "\n";
        return;
    } while (next_permutation(perm.begin(), perm.end()));
    if (!possible) {
        cout << "-1\n";
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}