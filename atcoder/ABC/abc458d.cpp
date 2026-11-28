#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    ll x, q;
    cin >> x >> q;
    indexed_set<pll> is;
    map<ll, ll> cnt;
    cnt[x]++;
    is.insert({x, cnt[x]});

    for (ll i = 0; i < q; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        cnt[ai]++;
        is.insert({ai, cnt[ai]});
        cnt[bi]++;
        is.insert({bi, cnt[bi]});
        cout << is.find_by_order(i + 1)->first << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}