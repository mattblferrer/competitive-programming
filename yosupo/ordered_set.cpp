#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    ll n, q;
    cin >> n >> q;
    indexed_set<ll> s;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        s.insert(ai);
    }
    for (ll i = 0; i < q; i++) {
        ll t, x;
        cin >> t >> x;
        if (t == 0) s.insert(x);
        else if (t == 1) s.erase(x);
        else if (t == 2) {
            if (s.size() < x) cout << "-1\n";
            else cout << *s.find_by_order(x - 1) << "\n";
        }
        else if (t == 3) cout << s.order_of_key(x + 1) << "\n";
        else if (t == 4) {
            auto it = s.find_by_order(s.order_of_key(x + 1) - 1);
            if (it == end(s)) cout << "-1\n";
            else cout << *it << "\n";
        }
        else if (t == 5) {
            auto it = s.find_by_order(s.order_of_key(x));
            if (it == end(s)) cout << "-1\n";
            else cout << *it << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}