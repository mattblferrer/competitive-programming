#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    bool is_min = false;
    map<ll, vector<ll>> queries;
    map<ll, ll> ans;

    for (ll qi = 0; qi < q; qi++) {
        ll x;
        cin >> x;
        queries[x].push_back(qi);
    }

    ll curr = 0;
    for (const auto &[x, vec] : queries) {
        sort(a.begin(), a.end());
        if (x == 0) {
            for (ll qi : vec) ans[qi] = a[n - 1] - a[0];
        }
        for (ll k = curr; k < x; k++) {
            if (is_min) break;

            vector<ll> prs;
            for (ll i = 0; i < n; i++) {
                for (ll j = i + 1; j < n; j++) {
                    prs.push_back(a[i] ^ a[j]);
                }
            }
            sort(prs.begin(), prs.end());
            a.assign(prs.begin(), prs.begin() + n);
            for (ll qi : vec) ans[qi] = a[n - 1] - a[0];
            if (ans[vec.front()] == 0) is_min = true;
        }
        if (is_min) break;
        curr = x;
    }
    for (ll qi = 0; qi < q; qi++) cout << ans[qi] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}