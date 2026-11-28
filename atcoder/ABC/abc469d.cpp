#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    map<ll, ll> one;
    map<pll, ll> both;
    for (ll i = 0; i < m; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        one[ai]++;
        one[bi]++;
        both[{ai, bi}]++;
    }

    vector<pll> one_vec;
    for (auto &pair : one) one_vec.push_back({pair.second, pair.first});
    sort(one_vec.begin(), one_vec.end(), greater<>());

    set<pll> ans_set;
    for (ll i = 0; i < one_vec.size(); i++) {
        ll u = one_vec[i].second, cnt_u = one_vec[i].first;
        if (cnt_u == m) {
            for (ll j = 1; j <= n; j++) {
                if (u == j) continue;
                ans_set.insert({min(u, j), max(u, j)});
            }
            continue;
        }
        for (ll j = 0; j < one_vec.size(); j++) {
            if (i == j) continue;
            ll v = one_vec[j].second, cnt_v = one_vec[j].first;
            if (cnt_u + cnt_v < m) break;
            if (u > v) {
                swap(u, v);
                swap(cnt_u, cnt_v);
            }
            ll cnt_both = both[{u, v}];

            if ((cnt_u + cnt_v - cnt_both) == m) {
                ans_set.insert({u, v});
            }
        }
    }
    cout << ans_set.size() << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}