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
    map<ll, deque<ll>> idx;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        idx[ai].push_back(i);
    }
    vector<ll> nums = {4, 8, 15, 16, 23, 42};
    ll ans = 0;
    while (true) {
        ll curr = -1;
        for (ll k : nums) {
            if (idx[k].empty()) {
                cout << n - ans * 6 << "\n";
                return;
            }
            while (idx[k][0] < curr) {
                idx[k].pop_front();
                if (idx[k].empty()) {
                    cout << n - ans * 6 << "\n";
                    return;
                }
            }
            curr = idx[k].front();
            idx[k].pop_front();
        }
        ans++;
    }
    cout << n - ans * 6 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}