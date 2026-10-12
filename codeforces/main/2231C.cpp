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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    set<ll> available;
    map<ll, ll> pos;
    pos[1] = pos[2] = 0;

    for (ll i = 0; i < n; i++) {
        set<ll> curr = {1, 2};
        if (a[i] == 1) {  // 1 -> 2 -> 1
            pos[2]++;
        }
        else {  // always ends in 4 -> 2 -> 1
            ll ctr = 0;
            if ((i == 0) || (available.count(a[i]))) {
                curr.insert(a[i]);
                pos[a[i]] += ctr;
            }

            while (a[i] != 1) {
                if (a[i] % 2 == 0) a[i] /= 2;
                else a[i]++;
                ctr++;
                if ((i == 0) || (available.count(a[i]))) {
                    curr.insert(a[i]);
                    pos[a[i]] += ctr;
                }
            }
        }
        if (i == 0) available = curr;
        set<ll> new_set;
        for (ll bi : available) {
            if (curr.count(bi)) {
                new_set.insert(bi);
            }
        }
        available = new_set;
    }
    ll ans = INF;
    for (auto &[bi, c] : pos) {
        if (available.count(bi) == 0) continue;
        ans = min(ans, c);
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